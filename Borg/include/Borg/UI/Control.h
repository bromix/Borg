#pragma once
#include "IControl.h"

namespace Borg::UI
{
    class Control : public virtual IControl
    {
    public:
        ~Control();
        Control();
        Control(const Ref<UI::IControl> &parent);
        UI::Handle Handle() const override;
        void SetText(const String &text) override;
        Borg::Ref<UI::IControl> GetParent() const override;
        int DeviceDpi() const override;
        void BringToFront() override;
        bool IsEnabled() const override;
        void SetEnabled(bool enabled) override;
        bool IsVisible() const override;
        void SetVisible(bool visible) override;
        void SetBackColor(const Drawing::Color &color) override;
        Drawing::Color GetBackColor() const override;
        Drawing::Rectangle GetBounds() const override;
        Drawing::Size GetSize() const override;
        void SetSize(const Drawing::Size &size) override;
        Drawing::Rectangle GetClientRectangle() const override;
        Drawing::Size GetClientSize() const override;
        Drawing::Point GetLocation() const override;
        void SetLocation(const Drawing::Point &point) override;
        void Invalidate() override;

        static Ref<IControl> CreateFrom(const UI::Handle &handle);

    protected:
        class ControlImpl;
        Ref<ControlImpl> m_Impl;
        void onSizeChanged(EventArgs e) override;
        void onMessage(UI::Message &message) override;
    };
}