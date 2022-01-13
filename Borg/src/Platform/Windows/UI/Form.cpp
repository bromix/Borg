#include "Borg/UI/Form.h"
#include "Borg/Exception.h"

namespace Borg::UI
{
    constexpr const wchar_t *BORG_UI_FORM_CLASSNAME = L"Borg::UI::Form";

    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        auto form = (Form *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

        switch (message)
        {
        case WM_SIZE:
            // if (webview != nullptr)
            //     webview->update_size();
            break;
        case WM_ERASEBKGND:
        {
            auto hdc = (HDC)wParam;
            RECT rc;
            GetClientRect(form->Handle(), &rc);
            HBRUSH brush = ::CreateSolidBrush(form->GetBackColor().ToBgr());
            auto ret = FillRect(hdc, &rc, brush);
            return 1L;
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hWnd, message, wParam, lParam);
            break;
        }

        return 0;
    }

    void registerForm(HINSTANCE hInst)
    {
        static std::once_flag createWindowOnce;
        // FIXME: make this cleaner.
        std::call_once(createWindowOnce, [hInst]()
                       {
                           WNDCLASSEXW wcex;
                           wcex.cbSize = sizeof(WNDCLASSEXW);
                           wcex.style = CS_HREDRAW | CS_VREDRAW;
                           wcex.lpfnWndProc = WndProc;
                           wcex.cbClsExtra = 0;
                           wcex.cbWndExtra = 0;
                           wcex.hInstance = hInst;
                           wcex.hIcon = LoadIcon(hInst, IDI_APPLICATION);
                           wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
                           wcex.hbrBackground = nullptr; //(HBRUSH)(COLOR_WINDOW + 1);
                           wcex.lpszMenuName = NULL;
                           wcex.lpszClassName = BORG_UI_FORM_CLASSNAME;
                           wcex.hIconSm = LoadIcon(hInst, IDI_APPLICATION);
                           if (!RegisterClassExW(&wcex))
                           {
                               MessageBoxA(nullptr, "Call to RegisterClassEx failed!", "Windows Desktop Guided Tour", 0);
                               return;
                           } });
    }

    Form::Form() : Control()
    {
        registerForm(GetModuleHandle(0));

        m_Handle = ::CreateWindowExW(
            WS_EX_LEFT, // the default.
            BORG_UI_FORM_CLASSNAME,
            nullptr,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            nullptr,
            nullptr,
            GetModuleHandle(0),
            nullptr);

        SetWindowLongPtr(m_Handle, GWLP_USERDATA, (LONG_PTR)this);

        // Set the default background color.
        m_BackgroundColor = Color::FromArgb(::GetSysColor(COLOR_WINDOW));
    }

    Form::Form(const UI::Handle &handle) : Control(handle) {}

    Ref<UI::IForm> Form::GetOwner() const
    {
        return UI::Form::CreateFrom(::GetWindow(m_Handle, GW_OWNER));
    }

    void Form::SetOwner(const Ref<UI::IForm> &owner)
    {
        throw NotImplementedException();
    }

    void Form::CenterToParent()
    {
        auto parent = GetParent();
        if (!parent)
            CenterToScreen();

        // FIXME: calculate new position.
        throw NotImplementedException();
    }

    void Form::CenterToScreen()
    {
        throw NotImplementedException();
    }

    UI::DialogResult Form::ShowDialog()
    {
        ::ShowWindow(m_Handle, SW_SHOWDEFAULT);

        MSG msg;
        while (::GetMessage(&msg, nullptr, 0, 0))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }

        return UI::DialogResult::None;
    }

    void Form::SetBackColor(const Color &color)
    {
        m_BackgroundColor = color;
    }

    Color Form::GetBackColor() const
    {
        return m_BackgroundColor;
    }
}