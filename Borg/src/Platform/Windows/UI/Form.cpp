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
            return 1;
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
            WS_OVERLAPPED,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            nullptr,
            nullptr,
            GetModuleHandle(0),
            nullptr);

        SetWindowLongPtr(m_Handle, GWLP_USERDATA, (LONG_PTR)this);

        // Set the default background color.
        m_BackgroundColor = Color::FromArgb(::GetSysColor(COLOR_WINDOW));

        // Set default border style
        SetFormBorderStyle(UI::FormBorderStyle::Sizable);
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

    void Form::SetFormBorderStyle(FormBorderStyle style)
    {
        if (style == FormBorderStyle::None)
        {
            ::SetWindowLong(m_Handle, GWL_STYLE, WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPED | WS_MAXIMIZEBOX);
            ::SetWindowLong(m_Handle, GWL_EXSTYLE, WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_CONTROLPARENT | WS_EX_APPWINDOW);
        }
        else if (style == FormBorderStyle::Sizable)
        {
            ::SetWindowLong(m_Handle, GWL_STYLE, WS_CAPTION | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_THICKFRAME | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
            ::SetWindowLong(m_Handle, GWL_EXSTYLE, WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT | WS_EX_APPWINDOW);
        }
        else if (style == FormBorderStyle::FixedSingle)
        {
            ::SetWindowLong(m_Handle, GWL_STYLE, WS_CAPTION | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
            ::SetWindowLong(m_Handle, GWL_EXSTYLE, WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT | WS_EX_APPWINDOW);
        }
        else if (style == FormBorderStyle::Fixed3D)
        {
            ::SetWindowLong(m_Handle, GWL_STYLE, WS_CAPTION | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
            ::SetWindowLong(m_Handle, GWL_EXSTYLE, WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_CONTROLPARENT | WS_EX_APPWINDOW);
        }
        else if (style == FormBorderStyle::FixedDialog)
        {
            ::SetWindowLong(m_Handle, GWL_STYLE, WS_CAPTION | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
            ::SetWindowLong(m_Handle, GWL_EXSTYLE, WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT | WS_EX_APPWINDOW);
        }
        else if (style == FormBorderStyle::FixedToolWindow)
        {
            ::SetWindowLong(m_Handle, GWL_STYLE, WS_CAPTION | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
            ::SetWindowLong(m_Handle, GWL_EXSTYLE, WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_TOOLWINDOW | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT | WS_EX_APPWINDOW);
        }
        else if (style == FormBorderStyle::SizableToolWindow)
        {
            ::SetWindowLong(m_Handle, GWL_STYLE, WS_CAPTION | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_THICKFRAME | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
            ::SetWindowLong(m_Handle, GWL_EXSTYLE, WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR | WS_EX_TOOLWINDOW | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT | WS_EX_APPWINDOW);
        }
        else
            throw InvalidEnumArgumentException("The value specified is outside the range of valid values.");

        Refresh();
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
        ::SetWindowPos(m_Handle, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);

        MSG msg;
        while (::GetMessage(&msg, nullptr, 0, 0))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }

        return UI::DialogResult::None;
    }
}