#include "Borg/Color.h"

namespace Borg
{
    uint8_t Color::A() const
    {
        return m_A;
    }

    uint8_t Color::R() const
    {
        return m_R;
    }

    uint8_t Color::G() const
    {
        return m_G;
    }

    uint8_t Color::B() const
    {
        return m_B;
    }

    uint32_t Color::ToArgb() const
    {
        static uint32_t argb = (m_A << 24) + (m_R << 16) + (m_G << 8)  + m_B;
        return argb;
    }

    Color Color::FromArgb(uint8_t r, uint8_t g, uint8_t b)
    {
        Color color;
        color.m_A = 255;
        color.m_R = r;
        color.m_G = g;
        color.m_B = b;

        return color;
    }

    Color Color::Black = Color::FromArgb(0, 0, 0);
}