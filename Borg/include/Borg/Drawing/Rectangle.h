#pragma once
#include <cstdint>

namespace Borg::Drawing
{
    class Rectangle
    {
    public:
        /**
         * @brief Initializes a new instance of the Rectangle class with the specified location and size.
         * 
         * @param x 
         * @param y 
         * @param width 
         * @param height 
         */
        Rectangle(int32_t x, int32_t y, int32_t width, int32_t height);
    };
}