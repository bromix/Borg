#include "Borg/Drawing/Point.h"

namespace Borg::Drawing
{
    Point::Point(int32_t x, int32_t y) : X(x), Y(y) {}

    bool Point::operator==(const Point &rhs) const
    {
        return X == rhs.X && Y == rhs.Y;
    }
    
    bool Point::operator!=(const Point &rhs) const
    {
        return !(*this == rhs);
    }
}