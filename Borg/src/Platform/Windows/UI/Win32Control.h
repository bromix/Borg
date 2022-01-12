#pragma once
#include "Borg/UI/IControl.h"

namespace Borg::UI
{
    class Win32Control : public Borg::UI::IControl
    {
    public:
        Win32Control(const UI::Handle &handle);
        ~Win32Control() = default;

        UI::Handle Handle() const override;
        void BringToFront() override;
        bool IsEnabled() const override;
        void SetEnabled(bool) override;
        bool IsVisible() const override;
        void SetVisible(bool visible) override;

    protected:
        UI::Handle m_Handle;
    };
}