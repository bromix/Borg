#pragma once
#include <cstdint>
#include "Size.h"
#include "Point.h"

namespace Borg::Drawing
{
    class Rectangle : public virtual Point, public virtual Size
    {
    public:
        Rectangle() = default;

        /**
         * @brief Initializes a new instance of the Rectangle class with the specified location and size.
         *
         * @param x
         * @param y
         * @param width
         * @param height
         */
        Rectangle(int32_t x, int32_t y, int32_t width, int32_t height);

        /**
         * @brief Gets the coordinates of the upper-left corner of this Rectangle structure.
         *
         * @return Drawing::Point
         */
        Drawing::Point GetLocation() const;

        /**
         * @brief Gets the size of this Rectangle.
         *
         * @return Drawing::Size
         */
        Drawing::Size GetSize() const;

        /**
         * @brief Centers the position of the Rectangle within the bounds of the parent Rectangle.
         * 
         * @param parent 
         * @return Drawing::Rectangle 
         */
        Drawing::Rectangle CenterTo(const Drawing::Rectangle &parent) const;

        bool operator==(const Drawing::Rectangle &rhs) const;
        bool operator!=(const Drawing::Rectangle &rhs) const;
    };
}