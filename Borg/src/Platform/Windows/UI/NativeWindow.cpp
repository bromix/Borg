#include "NativeWindow.h"
#include "../Windows.h"

namespace Borg::UI::Windows
{
    LRESULT CALLBACK SubClassWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
    {
        // Restore the original window procedure.
        if (uMsg == WM_NCDESTROY)
        {
            RemoveWindowSubclass(hWnd, SubClassWndProc, uIdSubclass);
            return DefSubclassProc(hWnd, uMsg, wParam, lParam);
        }

        // If our pointer is of NativeWindow, call the WndProc.
        NativeWindow *nativeWindow = reinterpret_cast<NativeWindow *>(dwRefData);
        if (nativeWindow != nullptr)
            return nativeWindow->WndProc(hWnd, uMsg, wParam, lParam);

        // Fallback to default window procedure.
        return DefSubclassProc(hWnd, uMsg, wParam, lParam);
    }

    NativeWindow::~NativeWindow()
    {
        OnMessage.Clear();
        releaseHandle();
    }

    UI::Handle NativeWindow::Handle() const
    {
        return m_Handle;
    }

    LRESULT NativeWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        if (OnMessage)
        {
            Message msg = {hWnd, uMsg, wParam, lParam};
            OnMessage(msg);
            return msg.Result;
        }
        return DefSubclassProc(hWnd, uMsg, wParam, lParam);
    }

    void NativeWindow::WrapHandle(const UI::Handle &handle)
    {
        // If the handle is already wrapped, do nothing.
        if (!m_IsWrapped)
            destroyHandle();

        // Set wrapped flag and store handle.
        m_IsWrapped = true;
        m_Handle = handle;
    }

    void NativeWindow::CreateHandle(const CreateParams &cp)
    {
        registerWindowClass(cp);

        WideStringBuffer className = Encoding::Convert<WideStringBuffer>(cp.ClassName);

        HINSTANCE hInstance = ::GetModuleHandleW(nullptr);

        m_Handle = ::CreateWindowExW(
            cp.ExStyle,
            className,
            nullptr,
            cp.Style,
            cp.X, cp.Y,
            cp.Width, cp.Height,
            cp.Parent,
            nullptr,
            hInstance,
            nullptr);

        static UINT_PTR nID = 0;
        nID++;
        m_SubClassWndProcId = nID;
        ::SetWindowSubclass(m_Handle, &SubClassWndProc, m_SubClassWndProcId, reinterpret_cast<DWORD_PTR>(this));
    }

    void NativeWindow::registerWindowClass(const CreateParams &cp)
    {
        HINSTANCE hInstance = ::GetModuleHandleW(nullptr);

        WideStringBuffer className = Encoding::Convert<WideStringBuffer>(cp.ClassName);

        WNDCLASSEXW wcex;
        wcex.cbSize = sizeof(WNDCLASSEXW);
        wcex.style = cp.ClassStyle;
        wcex.lpfnWndProc = DefWindowProcW;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance;
        wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = nullptr;
        wcex.lpszClassName = className;
        wcex.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

        // let it fail
        ATOM atom = RegisterClassExW(&wcex);
    }

    void NativeWindow::destroyHandle()
    {
        // FIXME: needs lock
        if (m_Handle)
        {
            if (::DestroyWindow(m_Handle) == FALSE)
                throw InvalidOperationException("DestroyWindow returned FALSE");

            m_Handle = nullptr;
        }
    }

    void NativeWindow::releaseHandle()
    {
        if (!m_Handle)
            return;
        m_Handle = nullptr;
    }
}