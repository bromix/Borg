#pragma once
#include "Borg/List.h"
#include "Borg/String.h"
#include "Borg/Ref.h"
#include "Borg/UI/IControl.h"

namespace Borg
{
    class Screen
    {
    public:
        /**
         * @brief Gets a value indicating whether a particular display is the primary device.
         *
         * @return true
         * @return false
         */
        bool IsPrimary() const;

        /**
         * @brief Gets the device name associated with a display.
         *
         * @return String
         */
        String GetDeviceName() const;

        /**
         * @brief Gets the bounds of the display.
         * 
         * @return Drawing::Rectangle 
         */
        Drawing::Rectangle GetBounds() const;

        /**
         * @brief Gets the working area of the display. The working area is the desktop area of the display, excluding taskbars, docked windows, and docked tool bars.
         * 
         * @return Drawing::Rectangle 
         */
        Drawing::Rectangle GetWorkingArea() const;

        /**
         * @brief Gets a list of all displays on the system.
         * 
         * @return IList<Screen> 
         */
        static List<Screen> GetAllScreens();

        /**
         * @brief Gets the primary display.
         *
         * @return Ref<Screen>
         */
        static Screen PrimaryScreen();

        /**
         * @brief Retrieves a Screen for the display that contains the largest portion of the specified control.
         *
         * @param control
         * @return Ref<Screen>
         */
        static Screen FromControl(const UI::IControl &control);

        /**
         * @brief Retrieves a Screen for the display that contains the largest portion of the object referred to by the specified handle.
         *
         * @param handle
         * @return Ref<Screen>
         */
        static Screen FromHandle(const UI::Handle &handle);

    protected:
        int32_t m_DeviceDpi{96};
        Drawing::Rectangle m_Bounds{0, 0, 0, 0};
        Drawing::Rectangle m_WorkingArea{0, 0, 0, 0};
        String m_DeviceName{"DISPLAY"};
        bool m_IsPrimary{false};
    };
}