#pragma once
#include "IForm.h"
#include "Control.h"

namespace Borg::UI
{
    class Form : public Control, public IForm
    {
    public:
        ~Form();
        Form();
        Form(const Ref<UI::IForm> &owner);
        Ref<IForm> GetOwner() const override;
        void SetOpacity(double opacity) override;
        double GetOpacity() const override;
        void SetFormBorderStyle(FormBorderStyle style) override;
        UI::FormBorderStyle GetFormBorderStyle() const override;
        void CenterToParent() override;
        void CenterToScreen() override;
        void SetShowInTaskbar(bool show) override;
        bool GetShowInTaskbar() const override;
        void Close() override;
        void Show() override;
        UI::DialogResult ShowDialog() override;

        static Ref<Form> CreateFrom(const UI::Handle &handle);

    protected:
        void onClosed(const UI::FormClosedEventArgs &e) override;
        UI::Message::Result onMessage(const UI::Message &message) override;
    };
}