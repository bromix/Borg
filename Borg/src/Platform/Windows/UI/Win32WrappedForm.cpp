#include "Win32WrappedForm.h"

namespace Borg::UI
{
    Ref<IForm> IForm::CreateWrappedForm(const UI::Handle &handle)
    {
        return CreateRef<Win32WrappedForm>(handle);
    }

    Win32WrappedForm::Win32WrappedForm(const UI::Handle &handle): m_Handle(handle)
    {
    }

    Ref<UI::IForm> Win32WrappedForm::GetOwner() const
    {
        if (this->GetParent() == nullptr)
            return nullptr;

        return RefAs<UI::IForm>(this->GetParent());
    }

    void Win32WrappedForm::SetOpacity(double opacity)
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

    double Win32WrappedForm::GetOpacity() const
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

    void Win32WrappedForm::SetFormBorderStyle(FormBorderStyle style)
    {
    }

    FormBorderStyle Win32WrappedForm::GetFormBorderStyle() const
    {
        throw InvalidOperationException("Could not determine FormBorderStyle.");
    }

    void Win32WrappedForm::SetShowInTaskbar(bool show)
    {
        auto exStyle = ::GetWindowLongW(m_Handle, GWL_EXSTYLE);

        if (show)
            exStyle |= WS_EX_APPWINDOW;
        else
            exStyle &= ~WS_EX_APPWINDOW;

        ::SetWindowLongW(m_Handle, GWL_EXSTYLE, exStyle);
        ::SetWindowPos(m_Handle, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }

    bool Win32WrappedForm::GetShowInTaskbar() const
    {
        auto exStyle = ::GetWindowLongW(m_Handle, GWL_EXSTYLE);
        return (exStyle & WS_EX_APPWINDOW) == WS_EX_APPWINDOW;
    }

    void Win32WrappedForm::Close()
    {
        ::PostMessageW(m_Handle, WM_CLOSE, 0, 0);
    }

    void Win32WrappedForm::Show()
    {
        ::ShowWindow(m_Handle, SW_SHOWDEFAULT);
        ::SetWindowPos(m_Handle, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }

    UI::DialogResult Win32WrappedForm::ShowDialog()
    {
        Show();

        MSG msg;
        while (::GetMessage(&msg, nullptr, 0, 0))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }

        return m_DialogResult;
    }

    void Win32WrappedForm::onMessage(UI::Message &message)
    {
    }

    UI::Handle Win32WrappedForm::Handle() const
    {
        return m_Handle;
    }

    void Win32WrappedForm::SetText(const String &text)
    {
        ::SetWindowTextW(m_Handle, Encoding::Convert<WideStringBuffer>(text));
    }

    Ref<UI::IControl> Win32WrappedForm::GetParent() const
    {
        return nullptr;
    }

    int Win32WrappedForm::DeviceDpi() const
    {
        return 0;
    }

    void Win32WrappedForm::BringToFront()
    {
        if(IsEnabled())
            ::BringWindowToTop(m_Handle);
    }

    bool Win32WrappedForm::IsEnabled() const
    {
        return ::IsWindowEnabled(m_Handle) == TRUE;
    }

    void Win32WrappedForm::SetEnabled(bool enabled)
    {
        ::EnableWindow(m_Handle, enabled ? TRUE : FALSE);
    }

    bool Win32WrappedForm::IsVisible() const
    {
        return ::IsWindowVisible(m_Handle) == TRUE;
    }

    void Win32WrappedForm::SetVisible(bool visible)
    {
        ::ShowWindow(m_Handle, SW_SHOWDEFAULT);
    }

    void Win32WrappedForm::SetBackColor(const Drawing::Color &color)
    {
    }

    Drawing::Color Win32WrappedForm::GetBackColor() const
    {
        return Drawing::Color::Black;
    }

    Drawing::Rectangle Win32WrappedForm::GetBounds() const
    {
        RECT rc{0};
        if (::GetWindowRect(m_Handle, &rc) != TRUE)
            throw InvalidOperationException("::GetWindowRect did not return TRUE.");

        return Drawing::Rectangle(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
    }

    Drawing::Size Win32WrappedForm::GetSize() const
    {
        return GetBounds().GetSize();
    }

    void Win32WrappedForm::SetSize(const Drawing::Size &size)
    {
        ::SetWindowPos(m_Handle, nullptr, 0, 0, size.Width, size.Height, SWP_NOMOVE | SWP_NOREPOSITION);
    }

    Drawing::Rectangle Win32WrappedForm::GetClientRectangle() const
    {
        RECT rc{0};
        if (::GetClientRect(m_Handle, &rc) != TRUE)
            throw InvalidOperationException("::GetClientRect did not return TRUE.");

        return Drawing::Rectangle(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
    }

    Drawing::Size Win32WrappedForm::GetClientSize() const
    {
        return GetClientRectangle().GetSize();
    }

    Drawing::Point Win32WrappedForm::GetLocation() const
    {
        return GetBounds().GetLocation();
    }

    void Win32WrappedForm::SetLocation(const Drawing::Point &point)
    {
        ::SetWindowPos(m_Handle, nullptr, point.X, point.Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    }

    void Win32WrappedForm::Invalidate()
    {
        if (IsVisible())
            ::RedrawWindow(m_Handle, nullptr, nullptr, RDW_ERASE | RDW_INVALIDATE);
    }

    void Win32WrappedForm::onSizeChanged(EventArgs e)
    {
        // TODO: invoke EventHandler
        OutputDebugStringA("onSizeChanged\n");
    }

    #ifdef _WIN32
    void Win32WrappedForm::DragMove()
    {
        /*
        https://www.c-sharpcorner.com/UploadFile/GemingLeader/moving-a-form-without-the-title-bar/

        This will simulate dragging via Titlebar.

        FIXME: https://docs.microsoft.com/en-us/dotnet/api/system.windows.window.dragmove?view=windowsdesktop-6.0
        */
        ReleaseCapture();
        ::SendMessage(m_Handle,   // Form handle
                      WM_NCLBUTTONDOWN, // Simulating the click
                      HTCAPTION,        // Attaching it to the title bar
                      0);               // No further options required
    }
#endif

    void Win32WrappedForm::CenterToParent()
    {
        auto parent = this->GetParent();
        if (!parent)
        {
            CenterToScreen();
            return;
        }

        auto centeredRect = this->GetBounds().CenterTo(parent->GetBounds());
        SetLocation({centeredRect.X, centeredRect.Y});
    }

    void Win32WrappedForm::CenterToScreen()
    {
    }

    void Win32WrappedForm::onClosed(const UI::FormClosedEventArgs &e)
    {
        // TODO: emit FormClosed Events.
        if (auto parent = this->GetOwner())
            parent->BringToFront();
    }

    void Win32WrappedForm::SetDialogResult(UI::DialogResult dialogResult)
    {
    }

    UI::DialogResult Win32WrappedForm::GetDialogResult() const
    {
        return UI::DialogResult::None;
    }
}