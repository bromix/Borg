#pragma once
#include "Borg/Ref.h"

namespace Borg::UI
{
    class IControl
    {
    public:
        ~IControl() = default;

        /**
         * @brief Gets a value indicating whether the control can respond to user interaction.
         * 
         * @return true 
         * @return false 
         */
        virtual bool IsEnabled() const = 0;

        /**
         * @brief Sets a value indicating whether the control can respond to user interaction.
         * 
         */
        virtual void SetEnabled(bool) = 0;
    };
}