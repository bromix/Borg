#include "Borg/UI/Control.h"
#include "Borg/Exception.h"
#include "../Windows.h"

namespace Borg::UI
{
    Control::Control() {}

    UI::Handle Control::Handle() const
    {
        return m_Handle;
    }

    void Control::SetText(const String &text)
    {
        ::SetWindowTextW(m_Handle, Encoding::Convert<WideCharBuffer>(text));
    }

    Ref<UI::IControl> Control::GetParent() const
    {
        return Control::CreateFrom(::GetParent(m_Handle));
    }

    int Control::DeviceDpi() const
    {
        HMONITOR monitor = ::MonitorFromWindow(m_Handle, MONITOR_DEFAULTTONEAREST);
        if (monitor == nullptr)
            return 96;

        UINT x, y;
        if (::GetDpiForMonitor(monitor, MDT_DEFAULT, &x, &y) == S_OK)
            return x;

        return 96;
    }

    void Control::BringToFront()
    {
        ::BringWindowToTop(m_Handle);
    }

    bool Control::IsEnabled() const
    {
        return ::IsWindowEnabled(m_Handle) == TRUE;
    }

    void Control::SetEnabled(bool enabled)
    {
        ::EnableWindow(m_Handle, enabled ? TRUE : FALSE);
    }

    bool Control::IsVisible() const
    {
        return ::IsWindowVisible(m_Handle) == TRUE;
    }

    void Control::SetVisible(bool visible)
    {
        ::ShowWindow(m_Handle, SW_SHOWDEFAULT);
    }

    void Control::SetBackColor(const Drawing::Color &color)
    {
        m_BackgroundColor = color;
        Invalidate();
    }

    Drawing::Color Control::GetBackColor() const
    {
        return m_BackgroundColor;
    }

    Drawing::Rectangle Control::GetBounds() const
    {
        RECT rc{0};
        if (::GetWindowRect(m_Handle, &rc) != TRUE)
            throw InvalidOperationException("::GetWindowRect did not return TRUE.");

        return Drawing::Rectangle(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
    }

    Drawing::Size Control::GetSize() const
    {
        return GetBounds();
    }

    void Control::SetSize(const Drawing::Size &size)
    {
        ::SetWindowPos(m_Handle, nullptr, 0, 0, size.Width, size.Height, SWP_NOMOVE | SWP_NOREPOSITION);
    }

    Drawing::Point Control::GetLocation() const
    {
        return GetBounds();
    }

    void Control::SetLocation(const Drawing::Point &point)
    {
        ::SetWindowPos(m_Handle, nullptr, point.X, point.Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    }

    void Control::Invalidate()
    {
        if (IsVisible())
            ::RedrawWindow(m_Handle, nullptr, nullptr, RDW_ERASE | RDW_INVALIDATE);
    }

    Ref<IControl> Control::CreateFrom(const UI::Handle &handle)
    {
        Ref<Control> control = CreateRef<Control>();
        control->m_Handle = handle;
        return control;
    }

    void Control::OnSizeChanged(EventArgs e)
    {
        // TODO: invoke EventHandler
        OutputDebugStringA("OnSizeChanged\n");
    }

    UI::Message::Result Control::WndProc(const UI::Message &message)
    {
        switch (message.Msg)
        {
        case WM_ERASEBKGND:
        {
            auto hdc = (HDC)message.WParam;
            RECT rc;
            GetClientRect(m_Handle, &rc);
            HBRUSH brush = ::CreateSolidBrush(GetBackColor().ToBgr());
            auto ret = FillRect(hdc, &rc, brush);
            return 1;
        }
        case WM_ENTERSIZEMOVE:
            OutputDebugStringA("WM_ENTERSIZEMOVE\n");
            break;
        case WM_EXITSIZEMOVE:
            OutputDebugStringA("WM_EXITSIZEMOVE\n");
            break;
        case WM_SIZE:
        {
            switch (message.WParam)
            {
            case SIZE_MINIMIZED:
                OutputDebugStringA("Minimizing\n");
                break;
            case SIZE_MAXIMIZED:
                OutputDebugStringA("Maximizing\n");
                break;
            // case SIZE_RESTORED:
            //     OutputDebugStringA("Restoring\n");
            //     break;
            default:
                OnSizeChanged({});
                break;
            }
        }
        break;
        }
        return DefWindowProcW(message.Handle, message.Msg, message.WParam, message.LParam);
    }
}