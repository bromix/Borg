#pragma once
#include "DialogResult.h"
#include "IControl.h"

namespace Borg::UI
{
    class IForm : public IControl
    {
    public:
        virtual ~IForm() = default;

        /**
         * @brief Shows the form as a modal dialog box.
         * 
         * @return DialogResult 
         */
        virtual DialogResult ShowDialog() = 0;
    };
}