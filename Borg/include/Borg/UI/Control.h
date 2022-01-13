#pragma once
#include "IControl.h"

namespace Borg::UI
{
    class Control : public virtual IControl
    {
    public:
        Control();
        Control(const UI::Handle &handle);
        UI::Handle Handle() const override;
        void SetText(const String &text) override;
        Ref<UI::IControl> GetParent() const override;
        void BringToFront() override;
        bool IsEnabled() const override;
        void SetEnabled(bool enabled) override;
        bool IsVisible() const override;
        void SetVisible(bool visible) override;
        void SetBackColor(const Color &color) override;
        Color GetBackColor() const override;
        void Refresh() override;

        // TODO: move impl. to cpp
        static Ref<IControl> CreateFrom(const UI::Handle &handle)
        {
            if(!handle)
                return nullptr;
            return CreateRef<Control>(handle);
        }

    protected:
        Color m_BackgroundColor;
        UI::Handle m_Handle;
    };
}