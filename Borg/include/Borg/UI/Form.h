#pragma once
#include "IForm.h"
#include "Control.h"

namespace Borg::UI
{
    class Form: public Control, public virtual IForm
    {
    public:
        Form();
        Form(const UI::Handle &handle);
        Ref<IForm> GetOwner() const override;
        void SetOwner(const Ref<IForm> &owner) override;
        void SetFormBorderStyle(FormBorderStyle style) override;
        void CenterToParent() override;
        void CenterToScreen() override;
        DialogResult ShowDialog() override;
        void SetBackColor(const Color &color) override;
        Color GetBackColor() const override;

        // TODO: move impl. to cpp
        static Ref<Form> CreateFrom(const UI::Handle& handle)
        {
            if(!handle)
                return nullptr;
            return CreateRef<Form>(handle);
        }

    private:
        Color m_BackgroundColor;
    };
}