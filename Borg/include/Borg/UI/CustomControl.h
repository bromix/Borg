#pragma once
#include "Control.h"

namespace Borg::UI
{
    class CustomControl : public UI::Control
    {
    public:
        CustomControl(const String &className);
        CustomControl(const Ref<UI::IControl> &parent, const String &className);
    };
}