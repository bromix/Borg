#pragma once
#include "Borg/UI/IForm.h"

namespace Borg::UI
{
    class Win32Form: public Borg::UI::IForm
    {
    public:
        Win32Form(const UI::Handle &handle);

        // IForm
        Ref<UI::IForm> Owner() const override;
        void SetOwner(const Ref<UI::IForm> &owner) override;
        UI::DialogResult ShowDialog() override;

        // IControl
        UI::Handle Handle() const override;
        bool IsEnabled() const override;
        void SetEnabled(bool) override;
    private:
        UI::Handle m_Handle;
    };
}