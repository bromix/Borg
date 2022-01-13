#include "Win32Control.h"
#include "Borg/Exception.h"

namespace Borg::UI
{
    Ref<IControl> IControl::CreateFrom(const UI::Handle &handle)
    {
        if(!handle)
            return nullptr;
        return CreateRef<Win32Control>(handle);
    }

    Win32Control::Win32Control(const UI::Handle &handle) : m_Handle(handle) {}

    UI::Handle Win32Control::Handle() const
    {
        return m_Handle;
    }

    Ref<UI::IControl> Win32Control::GetParent() const
    {
        return IControl::CreateFrom(::GetParent(m_Handle));
    }

    void Win32Control::BringToFront()
    {
        ::BringWindowToTop(m_Handle);
    }

    bool Win32Control::IsEnabled() const
    {
        return ::IsWindowEnabled(m_Handle) == TRUE;
    }

    void Win32Control::SetEnabled(bool enabled)
    {
        ::EnableWindow(m_Handle, enabled ? TRUE : FALSE);
    }

    bool Win32Control::IsVisible() const
    {
        return ::IsWindowVisible(m_Handle) == TRUE;
    }

    void Win32Control::SetVisible(bool visible)
    {
        ::ShowWindow(m_Handle, SW_SHOWDEFAULT);
    }
}