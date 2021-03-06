#pragma once
#include <cstdint>

namespace Borg::Drawing
{
    class Size
    {
    public:
        /**
         * @brief Default constructor.
         */
        Size() = default;

        /**
         * @brief Initializes a new instance of the Size structure from the specified dimensions.
         *
         * @param width
         * @param height
         */
        Size(int32_t width, int32_t height);

        /**
         * @brief Gets or sets the horizontal component of this Size structure.
         */
        int32_t Width{0};

        /**
         * @brief Gets or sets the vertical component of this Size structure.
         *
         */
        int32_t Height{0};

        bool operator==(const Size &rhs) const;
        bool operator!=(const Size &rhs) const;
    };
}