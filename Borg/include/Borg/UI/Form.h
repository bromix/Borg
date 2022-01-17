#pragma once
#include "IForm.h"
#include "Control.h"

namespace Borg::UI
{
    class Form : public Control, public virtual IForm
    {
    public:
        Form();
        Form(const UI::IForm* owner);
        Ref<IForm> GetOwner() const override;
        void SetOpacity(double opacity) override;
        double GetOpacity() const override;
        void SetFormBorderStyle(FormBorderStyle style) override;
        FormBorderStyle GetFormBorderStyle() const override;
        void CenterToParent() override;
        void CenterToScreen() override;
        void SetShowInTaskbar(bool show) override;
        bool GetShowInTaskbar() const override;
        DialogResult ShowDialog() override;

        static Ref<Form> CreateFrom(const UI::Handle &handle);

    protected:
        UI::Message::Result onMessage(const UI::Message &message) override;
    };
}