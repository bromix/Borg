#include "Borg/UI/Control.h"
#include "Borg/Exception.h"
#include "../Windows.h"

namespace Borg::UI
{
    Control::Control() {}

    Control::Control(const UI::Handle &handle) : m_Handle(handle)
    {
        if (!handle)
            throw ArgumentNullException("handle");
    }

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
        Refresh();
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

    void Control::Refresh()
    {
        ::RedrawWindow(m_Handle, nullptr, nullptr, RDW_ERASE | RDW_INVALIDATE);
    }
}