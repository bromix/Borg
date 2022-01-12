#pragma once
#include "Borg/UI/IForm.h"

namespace Borg::UI
{
    class Win32Form: public Borg::UI::IForm
    {
    public:
        Win32Form(const UI::Handle &handle);

        // IForm
        Ref<UI::IForm> GetOwner() const override;
        void SetOwner(const Ref<UI::IForm> &owner) override;
        void CenterToParent() override;
        UI::DialogResult ShowDialog() override;

        // IControl
        UI::Handle Handle() const override;
        void BringToFront() override;
        bool IsEnabled() const override;
        void SetEnabled(bool) override;
        bool IsVisible() const override;
        void SetVisible(bool visible) override;
    private:
        UI::Handle m_Handle;
    };
}