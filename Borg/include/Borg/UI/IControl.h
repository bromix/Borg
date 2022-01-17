#pragma once
#include "Borg/Ref.h"
#include "Message.h"
#include "Borg/EventArgs.h"
#include "Borg/Drawing/Color.h"
#include "Borg/Drawing/Rectangle.h"
#include "Handle.h"

namespace Borg::UI
{
    class IControl: public std::enable_shared_from_this<IControl>
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
        virtual Borg::Ref<UI::IControl> GetParent() const = 0;

        /**
         * @brief Gets the DPI value for the display device where the control is currently being displayed.
         *
         * @return int
         */
        virtual int DeviceDpi() const = 0;

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
         * @brief Gets the size and location of the control including its nonclient elements, in pixels, relative to the parent control.
         *
         * @return Drawing::Rectangle
         */
        virtual Drawing::Rectangle GetBounds() const = 0;

        /**
         * @brief Gets the height and width of the control.
         *
         * @return Drawing::Size
         */
        virtual Drawing::Size GetSize() const = 0;

        /**
         * @brief Sets the height and width of the control.
         *
         * @param size
         */
        virtual void SetSize(const Drawing::Size &size) = 0;

        /**
         * @brief Gets the rectangle that represents the client area of the control.
         * 
         * @return Drawing::Rectangle 
         */
        virtual Drawing::Rectangle GetClientRectangle() const = 0;

        /**
         * @brief Gets the height and width of the client area of the control.
         * 
         * @return Drawing::Size 
         */
        virtual Drawing::Size GetClientSize() const = 0;

        /**
         * @brief Gets the coordinates of the upper-left corner of the control relative to the upper-left corner of its container.
         *
         * @return Drawing::Point
         */
        virtual Drawing::Point GetLocation() const = 0;

        /**
         * @brief Sets the coordinates of the upper-left corner of the control relative to the upper-left corner of its container.
         *
         * @param point
         */
        virtual void SetLocation(const Drawing::Point &point) = 0;

        /**
         * @brief Invalidates the entire surface of the control and causes the control to be redrawn.
         */
        virtual void Invalidate() = 0;

    protected:
        /**
         * @brief Raises the SizeChanged event.
         * 
         * @param e 
         * 
         * @remark This function is called if the Size property is changed by either a programmatic modification or user interaction.
         */
        virtual void onSizeChanged (EventArgs e) = 0;

        virtual void initialize(const Ref<UI::IControl>& thisControl) {}

        virtual UI::Message::Result onMessage(const UI::Message &message) = 0;
    };
}