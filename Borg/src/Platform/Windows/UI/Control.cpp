#include "Borg/UI/Control.h"
#include "Borg/Exception.h"

namespace Borg::UI
{
    Control::Control()
    {

    }
    
    Control::Control(const UI::Handle &handle) : m_Handle(handle)
    {
        if (!handle)
            throw ArgumentNullException("handle");
    }

    UI::Handle Control::Handle() const
    {
        return m_Handle;
    }

    Ref<UI::IControl> Control::GetParent() const
    {
        return Control::CreateFrom(::GetParent(m_Handle));
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
}