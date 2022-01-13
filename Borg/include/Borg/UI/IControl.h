#pragma once
#include "Borg/Ref.h"
#include "Handle.h"

namespace Borg::UI
{
    class IControl
    {
    public:
        virtual ~IControl() = default;

        /**
         * @brief Gets the window handle that the control is bound to.
         * 
         * @return Handle 
         */
        virtual UI::Handle Handle() const = 0;

        /**
         * @brief Gets the parent container of the control.
         * 
         * @return Ref<UI::IControl> 
         */
        virtual Ref<UI::IControl> GetParent() const = 0;

        /**
         * @brief Brings the control to the front of the z-order.
         */
        virtual void BringToFront() = 0;

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
         * @param enabled 
         */
        virtual void SetEnabled(bool enabled) = 0;

        /**
         * @brief Gets a value indicating whether the control and all its child controls are displayed.
         * 
         * @return true 
         * @return false 
         */
        virtual bool IsVisible() const = 0;

        
        /**
         * @brief Sets a value indicating whether the control and all its child controls are displayed.
         * 
         * @param visible 
         */
        virtual void SetVisible(bool visible) = 0;

        static Ref<IControl> CreateFrom(const UI::Handle &handle);
    };
}