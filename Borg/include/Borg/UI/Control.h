#pragma once
#include "IControl.h"

namespace Borg::UI
{
    class Control : public virtual IControl
    {
    public:
        Control();
        Control(const Ref<UI::IControl> &parent);
        UI::Handle Handle() const override;
        void SetText(const String &text) override;
        Ref<UI::IControl> GetParent() const override;
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
        void assignParent(const Ref<UI::IControl> &parent);
        void onSizeChanged(EventArgs e) override;
        UI::Message::Result onMessage(const UI::Message &message) override;
        Drawing::Color m_BackgroundColor;
        UI::Handle m_Handle;

        Ref<UI::IControl> m_InternalParent;
    };
}