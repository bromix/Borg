#include "Borg/UI/Form.h"
#include "Borg/Screen.h"

namespace Borg::UI
{
    void Form::SetDialogResult(UI::DialogResult dialogResult)
    {
        m_DialogResult = dialogResult;
    }

    UI::DialogResult Form::GetDialogResult() const
    {
        return m_DialogResult;
    }

    void Form::CenterToParent()
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

    void Form::CenterToScreen()
    {
        auto primaryMonitor = Screen::FromHandle(this->Handle());

        auto centeredRect = this->GetBounds().CenterTo(primaryMonitor.GetBounds());
        SetLocation({centeredRect.X, centeredRect.Y});
    }

    void Form::onClosed(const UI::FormClosedEventArgs &e)
    {
        // TODO: emit FormClosed Events.
        if (auto parent = this->GetOwner())
            parent->BringToFront();
    }
}