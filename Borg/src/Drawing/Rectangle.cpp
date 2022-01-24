#include "Borg/Drawing/Rectangle.h"

namespace Borg::Drawing
{
    Rectangle::Rectangle(int32_t x, int32_t y, int32_t width, int32_t height)
        : Point(x, y), Size(width, height)
    {
    }

    Drawing::Point Rectangle::GetLocation() const
    {
        return *this;
    }

    Drawing::Size Rectangle::GetSize() const
    {
        return *this;
    }

    bool Rectangle::operator==(const Drawing::Rectangle &rhs) const
    {
        return GetLocation() == rhs.GetLocation() && GetSize() == rhs.GetSize();
    }

    bool Rectangle::operator!=(const Drawing::Rectangle &rhs) const
    {
        return !(*this == rhs);
    }
}