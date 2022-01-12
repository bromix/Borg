#pragma once
#include "Win32Control.h"
#include "Borg/UI/IForm.h"

namespace Borg::UI
{
    class Win32Form: public Win32Control, public UI::IForm
    {
    public:
        Win32Form(const UI::Handle &handle);
        ~Win32Form() = default;

        Ref<UI::IForm> GetOwner() const override;
        void SetOwner(const Ref<UI::IForm> &owner) override;
        void CenterToParent() override;
        void CenterToScreen() override;
        UI::DialogResult ShowDialog() override;
    };
}