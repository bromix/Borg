#pragma once
#include "IForm.h"
#include "Control.h"

namespace Borg::UI
{
    class Form : public Control, public virtual IForm
    {
    public:
        Form();
        Form(const Ref<UI::IForm> &owner);
        Form(const UI::Handle &handle);
        Ref<IForm> GetOwner() const override;
        void SetOpacity(double opacity) override;
        double GetOpacity() const override;
        void SetFormBorderStyle(FormBorderStyle style) override;
        void CenterToParent() override;
        void CenterToScreen() override;
        DialogResult ShowDialog() override;

        // TODO: move impl. to cpp
        static Ref<Form> CreateFrom(const UI::Handle &handle)
        {
            if (!handle)
                return nullptr;
            return CreateRef<Form>(handle);
        }
    };
}