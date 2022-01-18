#pragma once

#include "NativeWindow.h"

namespace Borg::UI
{
    class Control::ControlImpl: public Windows::NativeWindow
    {
    public:
        WeakRef<UI::IControl> m_InternalParent;
        Drawing::Color m_BackgroundColor =Drawing::Color::FromArgb(::GetSysColor(COLOR_WINDOW));
    };
}