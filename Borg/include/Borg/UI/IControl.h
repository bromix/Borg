#pragma once
#include "Borg/Ref.h"
#include "Borg/Drawing/Color.h"
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
         * @brief Gets or sets the text associated with this control.
         * 
         * @param text 
         */
        virtual void SetText(const String &text) = 0;

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

        /**
         * @brief Sets the background color for the control.
         *
         * @param color
         */
        virtual void SetBackColor(const Drawing::Color &color) = 0;

        /**
         * @brief Gets the background color for the control.
         *
         * @return Color
         */
        virtual Drawing::Color GetBackColor() const = 0;

        /**
         * @brief Forces the control to invalidate its client area and immediately redraw itself and any child controls.
         */
        virtual void Refresh() = 0;
    };
}