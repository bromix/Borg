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

#ifdef _WIN32
    void Form::DragMove()
    {
        /*
        https://www.c-sharpcorner.com/UploadFile/GemingLeader/moving-a-form-without-the-title-bar/

        This will simulate dragging via Titlebar.

        FIXME: https://docs.microsoft.com/en-us/dotnet/api/system.windows.window.dragmove?view=windowsdesktop-6.0
        */
        ReleaseCapture();
        ::SendMessage(this->Handle(),   // Form handle
                      WM_NCLBUTTONDOWN, // Simulating the click
                      HTCAPTION,        // Attaching it to the title bar
                      0);               // No further options required
    }
#endif

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