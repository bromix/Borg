#include "ClassFactory.h"

namespace Borg::UI
{
    class WndProxy
    {
    public:
        WndProxy(Func<LRESULT, const UI::Message &> &&wndProc) : m_wndProc(std::move(wndProc))
        {
        }

        LRESULT operator()(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
            return m_wndProc({hWnd, message, wParam, lParam});
        }

    private:
        Func<LRESULT, const UI::Message &> m_wndProc;
    };

    UI::Handle ClassFactory::Create(CREATESTRUCTW &cs, UINT classStyle, Func<LRESULT, const UI::Message &> &&onMessage)
    {
        if (cs.hInstance == nullptr)
            cs.hInstance = ::GetModuleHandleW(nullptr);

        if (!isRegistered(cs.lpszClass))
            registerClass(cs, classStyle);

        return createClass(cs, std::move(onMessage));
    }

    UI::Handle ClassFactory::createClass(CREATESTRUCTW &cs, Func<LRESULT, const UI::Message &> &&onMessage)
    {
        WndProxy *wndProxy = new WndProxy(std::move(onMessage));

        return ::CreateWindowExW(
            cs.dwExStyle,
            cs.lpszClass,
            nullptr,
            cs.style,
            cs.x, cs.y,
            cs.cx, cs.cy,
            cs.hwndParent,
            cs.hMenu,
            cs.hInstance,
            wndProxy);
    }

    bool ClassFactory::isRegistered(const String &className)
    {
        auto found = m_RegisteredClasses.find(className);
        return found != m_RegisteredClasses.end();
    }

    void ClassFactory::registerClass(CREATESTRUCTW &cs, UINT classStyle)
    {
        WNDCLASSEXW wcex;
        wcex.cbSize = sizeof(WNDCLASSEXW);
        wcex.style = classStyle;
        wcex.lpfnWndProc = ClassFactory::WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = cs.hInstance;
        wcex.hIcon = LoadIcon(cs.hInstance, IDI_APPLICATION);
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground = nullptr; //(HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = nullptr;
        wcex.lpszClassName = cs.lpszClass;
        wcex.hIconSm = LoadIcon(cs.hInstance, IDI_APPLICATION);

        ATOM atom = RegisterClassExW(&wcex);
        m_RegisteredClasses[cs.lpszClass] = atom;
    }

    LRESULT CALLBACK ClassFactory::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        WndProxy *wndProxy = nullptr;

        if (message == WM_NCCREATE)
        {
            LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
            wndProxy = static_cast<WndProxy *>(lpcs->lpCreateParams);
            ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(wndProxy));
        }
        else
            wndProxy = reinterpret_cast<WndProxy *>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

        if (message == WM_NCDESTROY)
        {
            wndProxy = reinterpret_cast<WndProxy *>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
            ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
            if (wndProxy)
            {
                delete wndProxy;
                wndProxy = nullptr;
            }
        }

        if (wndProxy)
            return (*wndProxy)(hWnd, message, wParam, lParam);

        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
}