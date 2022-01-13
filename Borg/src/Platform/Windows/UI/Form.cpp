#include "Borg/UI/Form.h"
#include "Borg/Exception.h"

namespace Borg::UI
{
    Form::Form(const UI::Handle &handle) : Control(handle) {}

    Ref<UI::IForm> Form::GetOwner() const
    {
        return nullptr;
    }

    void Form::SetOwner(const Ref<UI::IForm> &owner)
    {
        throw NotImplementedException();
    }

    void Form::CenterToParent()
    {
        throw NotImplementedException();
    }

    void Form::CenterToScreen()
    {
        throw NotImplementedException();
    }

    UI::DialogResult Form::ShowDialog()
    {
        throw NotImplementedException();
    }

    // UI::Handle Form::Handle() const
    // {
    //     return m_Handle;
    // }

    // void Form::BringToFront()
    // {
    //     ::BringWindowToTop(m_Handle);
    // }

    // bool Form::IsEnabled() const
    // {
    //     return ::IsWindowEnabled(m_Handle) == TRUE;
    // }

    // void Form::SetEnabled(bool enabled)
    // {
    //     ::EnableWindow(m_Handle, enabled ? TRUE : FALSE);
    // }

    // bool Form::IsVisible() const
    // {
    //     return ::IsWindowVisible(m_Handle) == TRUE;
    // }

    // void Form::SetVisible(bool visible)
    // {
    //     ::ShowWindow(m_Handle, SW_SHOWDEFAULT);
    // }
}