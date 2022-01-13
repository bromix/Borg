#pragma once
#include <cstdint>

namespace Borg
{
    class Color
    {
    public:
        uint8_t A() const;
        uint8_t R() const;
        uint8_t G() const;
        uint8_t B() const;

        uint32_t ToArgb() const;

        static Color FromArgb(uint8_t r, uint8_t g, uint8_t b);
        static Color Black;

    private:
        uint32_t m_Argb;
        uint8_t m_A;
        uint8_t m_R;
        uint8_t m_G;
        uint8_t m_B;
    };
}