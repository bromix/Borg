#include "Borg/Screen.h"

namespace Borg
{
    bool Screen::IsPrimary() const
    {
        return m_IsPrimary;
    }

    String Screen::GetDeviceName() const
    {
        return m_DeviceName;
    }

    Drawing::Rectangle Screen::GetBounds() const
    {
        return m_Bounds;
    }

    Drawing::Rectangle Screen::GetWorkingArea() const
    {
        return m_WorkingArea;
    }

    Screen Screen::PrimaryScreen()
    {
        auto allScreens = GetAllScreens();
        for(auto screen : allScreens)
        {
            if(screen.IsPrimary())
                return screen;
        }

        throw InvalidOperationException("Failed to get primary monitor.");
    }
}