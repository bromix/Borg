#pragma once
#include "IControl.h"

namespace Borg::UI
{
    class Control : public virtual IControl
    {
    public:
        Control(const UI::Handle &handle);
        UI::Handle Handle() const override;
        Ref<UI::IControl> GetParent() const override;
        void BringToFront() override;
        bool IsEnabled() const override;
        void SetEnabled(bool enabled) override;
        bool IsVisible() const override;
        void SetVisible(bool visible) override;

        // TODO: move impl. to cpp
        static Ref<IControl> CreateFrom(const UI::Handle &handle)
        {
            if(!handle)
                return nullptr;
            return CreateRef<Control>(handle);
        }

    protected:
        UI::Handle m_Handle;
    };
}