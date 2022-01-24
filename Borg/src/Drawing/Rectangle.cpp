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

    Rectangle Rectangle::CenterTo(const Drawing::Rectangle &parent) const
    {
        int32_t x = parent.X + (parent.Width - Size::Width) / 2;
        int32_t y = parent.Y + (parent.Height - Size::Height) / 2;

        Rectangle centeredRectangle{x, y, Size::Width, Size::Height};
        return centeredRectangle;
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