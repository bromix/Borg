#pragma once
#include <cstdint>

namespace Borg::Drawing
{
    class Point
    {
    public:
        /**
         * @brief Default constructor.
         */
        Point() = default;

        /**
         * @brief Initializes a new instance of the Point struct with the specified coordinates.
         * 
         * @param x 
         * @param y 
         */
        Point(int32_t x, int32_t y);

        /**
         * @brief Gets or sets the x-coordinate of this Point.
         */
        int32_t X{0};

        /**
         * @brief Gets or sets the y-coordinate of this Point.
         * 
         */
        int32_t Y{0};

        Point operator-(const Drawing::Point& rhs)const;
        Point& operator-=(const Drawing::Point& rhs);

        Point operator+(const Drawing::Point& rhs)const;
        Point& operator+=(const Drawing::Point& rhs);

        bool operator==(const Drawing::Point &rhs) const;
        bool operator!=(const Drawing::Point &rhs) const;
    };
}