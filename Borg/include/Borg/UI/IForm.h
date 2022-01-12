#pragma once
#include "DialogResult.h"
#include "IControl.h"

namespace Borg::UI
{
    class IForm : public IControl
    {
    public:
        virtual DialogResult ShowDialog() = 0;
    };
}