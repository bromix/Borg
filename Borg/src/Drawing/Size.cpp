#include "Borg/Drawing/Size.h"

namespace Borg::Drawing
{
    Size::Size(int32_t width, int32_t height) : Height(height), Width(width) {}

    bool Size::operator==(const Size &rhs) const
    {
        return Width == rhs.Width && Height == rhs.Height;
    }
    
    bool Size::operator!=(const Size &rhs) const
    {
        return !(*this == rhs);
    }
}