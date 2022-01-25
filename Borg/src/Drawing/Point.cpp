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

    Point Point::operator-(const Drawing::Point &rhs) const
    {
        return {this->X - rhs.X, this->Y - rhs.Y};
    }

    Point &Point::operator-=(const Drawing::Point &rhs)
    {
        this->X -= rhs.X;
        this->Y -= rhs.Y;
        return *this;
    }

    Point Point::operator+(const Drawing::Point &rhs) const
    {
        return {this->X + rhs.X, this->Y + rhs.Y};
    }

    Point &Point::operator+=(const Drawing::Point &rhs)
    {
        this->X += rhs.X;
        this->Y += rhs.Y;
        return *this;
    }
}