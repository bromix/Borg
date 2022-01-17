#pragma once
#include "Control.h"

namespace Borg::UI
{
    class CustomControl : public virtual UI::Control
    {
    public:
        CustomControl(const Ref<UI::IControl> &parent, const String &className);
    };
}