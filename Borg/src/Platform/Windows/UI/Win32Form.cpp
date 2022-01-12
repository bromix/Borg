#include "Win32Form.h"
#include "Borg/Exception.h"

namespace Borg::UI
{
    Win32Form::Win32Form(const UI::Handle &handle) : m_Handle(handle) {}

    Ref<UI::IForm> Win32Form::Owner() const
    {
        return nullptr;
    }

    void Win32Form::SetOwner(const Ref<UI::IForm> &owner)
    {
        throw NotImplementedException();
    }

    UI::DialogResult Win32Form::ShowDialog()
    {
        throw NotImplementedException();
    }

    UI::Handle Win32Form::Handle() const
    {
        return m_Handle;
    }

    void Win32Form::BringToFront()
    {
        ::BringWindowToTop(m_Handle);
    }

    bool Win32Form::IsEnabled() const
    {
        return ::IsWindowEnabled(m_Handle) == TRUE;
    }

    void Win32Form::SetEnabled(bool enabled)
    {
        ::EnableWindow(m_Handle, enabled ? TRUE : FALSE);
    }
}