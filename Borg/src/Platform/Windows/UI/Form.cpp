#include "Borg/UI/Form.h"
#include "Borg/Exception.h"
#include "Borg/Types.h"
#include "ClassFactory.h"

namespace Borg::UI
{
    constexpr const long BORG_FORMBORDERSTYLE_SIZABLETOOLWINDOW_STYLE = WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_THICKFRAME | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    constexpr const long BORG_FORMBORDERSTYLE_SIZABLETOOLWINDOW_EXSTYLE = WS_EX_TOOLWINDOW | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT;

    constexpr const long BORG_FORMBORDERSTYLE_SIZABLE_STYLE = WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_THICKFRAME | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    constexpr const long BORG_FORMBORDERSTYLE_SIZABLE_EXSTYLE = WS_EX_WINDOWEDGE;

    constexpr const long BORG_FORMBORDERSTYLE_FIXEDTOOLWINDOW_STYLE = WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    constexpr const long BORG_FORMBORDERSTYLE_FIXEDTOOLWINDOW_EXSTYLE = WS_EX_TOOLWINDOW | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT;

    constexpr const long BORG_FORMBORDERSTYLE_FIXEDDIALOG_STYLE = WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    constexpr const long BORG_FORMBORDERSTYLE_FIXEDDIALOG_EXSTYLE = WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE;

    constexpr const long BORG_FORMBORDERSTYLE_FIXEDSINGLE_STYLE = WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    constexpr const long BORG_FORMBORDERSTYLE_FIXEDSINGLE_EXSTYLE = WS_EX_WINDOWEDGE;

    constexpr const long BORG_FORMBORDERSTYLE_FIXED3D_STYLE = WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    constexpr const long BORG_FORMBORDERSTYLE_FIXED3D_EXSTYLE = 0;

    constexpr const long BORG_FORMBORDERSTYLE_NONE_STYLE = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPED | WS_MAXIMIZEBOX;
    constexpr const long BORG_FORMBORDERSTYLE_NONE_EXSTYLE = 0;

    Form::~Form(){}

    Form::Form() : Form(nullptr) {}

    Form::Form(const Ref<UI::IForm> &owner) : Control(owner)
    {
        UI::Handle hOwner = UI::Handle::GetSafeFrom(m_InternalParent.lock());

        CREATESTRUCTW cs{0};
        cs.lpszClass = L"BORG::UI::FORM";
        cs.style = WS_OVERLAPPED;
        cs.dwExStyle = WS_EX_LEFT;
        cs.hwndParent = hOwner;
        cs.x = CW_USEDEFAULT;
        cs.y = CW_USEDEFAULT;
        cs.cx = CW_USEDEFAULT;
        cs.cy = CW_USEDEFAULT;

        auto classStyle = CS_HREDRAW | CS_VREDRAW;
        m_Handle = ClassFactory::Create(cs, classStyle, [this](const UI::Message &message)
                                        { return this->onMessage(message); });

        // Set default border style
        SetFormBorderStyle(UI::FormBorderStyle::Sizable);

        SetShowInTaskbar(true);
    }

    Ref<UI::IForm> Form::GetOwner() const
    {
        return nullptr;
    }

    void Form::SetOpacity(double opacity)
    {
        auto currentStyle = ::GetWindowLongW(m_Handle, GWL_EXSTYLE);

        if (opacity < 1.0)
        {
            // Add style.
            currentStyle |= WS_EX_LAYERED;
            ::SetWindowLongW(m_Handle, GWL_EXSTYLE, currentStyle);
            ::SetLayeredWindowAttributes(m_Handle, 0, opacity * 255, LWA_ALPHA);
        }
        else
        {
            ::SetLayeredWindowAttributes(m_Handle, 0, 255, LWA_ALPHA);

            // Remove style
            currentStyle &= ~WS_EX_LAYERED;
            ::SetWindowLongW(m_Handle, GWL_EXSTYLE, currentStyle);
        }

        Invalidate();
    }

    double Form::GetOpacity() const
    {
        auto currentStyle = ::GetWindowLongW(m_Handle, GWL_EXSTYLE);

        // Without WX_ES_LAYERED style opacity isn't possible.
        if ((currentStyle & WS_EX_LAYERED) == 0)
            return 1.0;

        BYTE alpha = 255;
        DWORD flags = 0;
        if (::GetLayeredWindowAttributes(m_Handle, 0, &alpha, &flags) != TRUE)
            return 1.0;

        // If LWA_ALPHA is set, we can calculate the opacity.
        if (flags == LWA_ALPHA)
            return alpha / 255.0;

        return 1.0;
    }

    void Form::SetFormBorderStyle(FormBorderStyle style)
    {
        auto defaultExStyles = WS_EX_CONTROLPARENT;

        // Some styles we need to keep if they are already set.
        auto currentExStyle = ::GetWindowLongW(m_Handle, GWL_EXSTYLE);
        if ((currentExStyle & WS_EX_LAYERED) == WS_EX_LAYERED)
            defaultExStyles |= WS_EX_LAYERED;

        if ((currentExStyle & WS_EX_APPWINDOW) == WS_EX_APPWINDOW)
            defaultExStyles |= WS_EX_APPWINDOW;

        // add LTR orientation styles
        defaultExStyles |= WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR;

        if (style == FormBorderStyle::None)
        {
            ::SetWindowLong(m_Handle, GWL_STYLE, BORG_FORMBORDERSTYLE_NONE_STYLE);
            ::SetWindowLong(m_Handle, GWL_EXSTYLE, defaultExStyles | BORG_FORMBORDERSTYLE_NONE_EXSTYLE);
        }
        else if (style == FormBorderStyle::Sizable)
        {
            ::SetWindowLong(m_Handle, GWL_STYLE, BORG_FORMBORDERSTYLE_SIZABLE_STYLE);
            ::SetWindowLong(m_Handle, GWL_EXSTYLE, defaultExStyles | BORG_FORMBORDERSTYLE_SIZABLE_EXSTYLE);
        }
        else if (style == FormBorderStyle::FixedSingle)
        {
            ::SetWindowLong(m_Handle, GWL_STYLE, BORG_FORMBORDERSTYLE_FIXEDSINGLE_STYLE);
            ::SetWindowLong(m_Handle, GWL_EXSTYLE, defaultExStyles | BORG_FORMBORDERSTYLE_FIXEDSINGLE_EXSTYLE);
        }
        else if (style == FormBorderStyle::Fixed3D)
        {
            ::SetWindowLong(m_Handle, GWL_STYLE, BORG_FORMBORDERSTYLE_FIXED3D_STYLE);
            ::SetWindowLong(m_Handle, GWL_EXSTYLE, defaultExStyles | BORG_FORMBORDERSTYLE_FIXED3D_EXSTYLE);
        }
        else if (style == FormBorderStyle::FixedDialog)
        {
            ::SetWindowLong(m_Handle, GWL_STYLE, BORG_FORMBORDERSTYLE_FIXEDDIALOG_STYLE);
            ::SetWindowLong(m_Handle, GWL_EXSTYLE, defaultExStyles | BORG_FORMBORDERSTYLE_FIXEDDIALOG_EXSTYLE);
        }
        else if (style == FormBorderStyle::FixedToolWindow)
        {
            ::SetWindowLong(m_Handle, GWL_STYLE, BORG_FORMBORDERSTYLE_FIXEDTOOLWINDOW_STYLE);
            ::SetWindowLong(m_Handle, GWL_EXSTYLE, defaultExStyles | BORG_FORMBORDERSTYLE_FIXEDTOOLWINDOW_EXSTYLE);
        }
        else if (style == FormBorderStyle::SizableToolWindow)
        {
            ::SetWindowLong(m_Handle, GWL_STYLE, BORG_FORMBORDERSTYLE_SIZABLETOOLWINDOW_STYLE);
            ::SetWindowLong(m_Handle, GWL_EXSTYLE, defaultExStyles | BORG_FORMBORDERSTYLE_SIZABLETOOLWINDOW_EXSTYLE);
        }
        else
            throw InvalidEnumArgumentException("The value specified is outside the range of valid values.");

        Invalidate();
    }

    FormBorderStyle Form::GetFormBorderStyle() const
    {
        auto style = ::GetWindowLongW(m_Handle, GWL_STYLE);
        auto exStyle = ::GetWindowLongW(m_Handle, GWL_EXSTYLE);

        // IMPORTANT !!! The order is important. The values with the most flags must be compared first.

        if ((style & BORG_FORMBORDERSTYLE_SIZABLETOOLWINDOW_STYLE) == BORG_FORMBORDERSTYLE_SIZABLETOOLWINDOW_STYLE &&
            (exStyle & BORG_FORMBORDERSTYLE_SIZABLETOOLWINDOW_EXSTYLE) == BORG_FORMBORDERSTYLE_SIZABLETOOLWINDOW_EXSTYLE)
            return FormBorderStyle::SizableToolWindow;

        if ((style & BORG_FORMBORDERSTYLE_SIZABLE_STYLE) == BORG_FORMBORDERSTYLE_SIZABLE_STYLE &&
            (exStyle & BORG_FORMBORDERSTYLE_SIZABLE_EXSTYLE) == BORG_FORMBORDERSTYLE_SIZABLE_EXSTYLE)
            return FormBorderStyle::Sizable;

        if ((style & BORG_FORMBORDERSTYLE_FIXEDTOOLWINDOW_STYLE) == BORG_FORMBORDERSTYLE_FIXEDTOOLWINDOW_STYLE &&
            (exStyle & BORG_FORMBORDERSTYLE_FIXEDTOOLWINDOW_EXSTYLE) == BORG_FORMBORDERSTYLE_FIXEDTOOLWINDOW_EXSTYLE)
            return FormBorderStyle::FixedToolWindow;

        if ((style & BORG_FORMBORDERSTYLE_FIXEDDIALOG_STYLE) == BORG_FORMBORDERSTYLE_FIXEDDIALOG_STYLE &&
            (exStyle & BORG_FORMBORDERSTYLE_FIXEDDIALOG_EXSTYLE) == BORG_FORMBORDERSTYLE_FIXEDDIALOG_EXSTYLE)
            return FormBorderStyle::FixedDialog;

        if ((style & BORG_FORMBORDERSTYLE_FIXEDSINGLE_STYLE) == BORG_FORMBORDERSTYLE_FIXEDSINGLE_STYLE &&
            (exStyle & BORG_FORMBORDERSTYLE_FIXEDSINGLE_EXSTYLE) == BORG_FORMBORDERSTYLE_FIXEDSINGLE_EXSTYLE)
            return FormBorderStyle::FixedSingle;

        if ((style & BORG_FORMBORDERSTYLE_FIXED3D_STYLE) == BORG_FORMBORDERSTYLE_FIXED3D_STYLE &&
            (exStyle & BORG_FORMBORDERSTYLE_FIXED3D_EXSTYLE) == BORG_FORMBORDERSTYLE_FIXED3D_EXSTYLE)
            return FormBorderStyle::Fixed3D;

        if ((style & BORG_FORMBORDERSTYLE_NONE_STYLE) == BORG_FORMBORDERSTYLE_NONE_STYLE &&
            (exStyle & BORG_FORMBORDERSTYLE_NONE_EXSTYLE) == BORG_FORMBORDERSTYLE_NONE_EXSTYLE)
            return FormBorderStyle::None;

        throw InvalidOperationException("Could not determine FormBorderStyle.");
    }

    void Form::CenterToParent()
    {
        auto parent = GetParent();
        if (!parent)
        {
            CenterToScreen();
            return;
        }

        auto parentRect = parent->GetBounds();
        auto thisSize = GetSize();

        int32_t x = parentRect.X + (parentRect.Width - thisSize.Width) / 2;
        int32_t y = parentRect.Y + (parentRect.Height - thisSize.Height) / 2;

        SetLocation({x, y});
    }

    void Form::CenterToScreen()
    {
        // FIXME:
        //throw NotImplementedException();
    }

    void Form::SetShowInTaskbar(bool show)
    {
        auto exStyle = ::GetWindowLongW(m_Handle, GWL_EXSTYLE);

        if (show)
            exStyle |= WS_EX_APPWINDOW;
        else
            exStyle &= ~WS_EX_APPWINDOW;

        ::SetWindowLongW(m_Handle, GWL_EXSTYLE, exStyle);
        ::SetWindowPos(m_Handle, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }

    bool Form::GetShowInTaskbar() const
    {
        auto exStyle = ::GetWindowLongW(m_Handle, GWL_EXSTYLE);
        return (exStyle & WS_EX_APPWINDOW) == WS_EX_APPWINDOW;
    }

    void Form::Close()
    {
        ::PostMessageW(m_Handle, WM_CLOSE, 0, 0);
    }

    void Form::Show()
    {
        ::ShowWindow(m_Handle, SW_SHOWDEFAULT);
        ::SetWindowPos(m_Handle, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }

    UI::DialogResult Form::ShowDialog()
    {
        Show();

        MSG msg;
        while (::GetMessage(&msg, nullptr, 0, 0))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }

        return UI::DialogResult::None;
    }

    Ref<Form> Form::CreateFrom(const UI::Handle &handle)
    {
        Ref<Form> form = CreateRef<Form>();
        form->m_Handle = handle;
        return form;
    }

    void Form::onClosed(const UI::FormClosedEventArgs &e)
    {
        // TODO: emit FormClosed Events.
    }

    UI::Message::Result Form::onMessage(const UI::Message &message)
    {
        switch (message.Msg)
        {
        case WM_CLOSE:
            // TODO: process onClosing()
            onClosed({});
            ::DestroyWindow(m_Handle);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }

        return Control::onMessage(message);
    }
}