#include "Borg/Drawing/Color.h"

namespace Borg::Drawing
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
        return (m_A << 24) + (m_R << 16) + (m_G << 8) + m_B;
    }

    uint32_t Color::ToBgr() const
    {
        return (m_R) | (m_G << 8) | (m_B << 16);
    }

    Color Color::FromArgb(uint32_t argb)
    {
        Color color;
        color.m_A = (argb & 0xFF000000) >> 24;
        color.m_R = (argb & 0x00FF0000) >> 16;
        color.m_G = (argb & 0x0000FF00) >> 8;
        color.m_B = (argb & 0x000000FF);
        return color;
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

    Color Color::Red = Color::FromArgb(0xFFFF0000);
    Color Color::Green = Color::FromArgb(0xFF008000);
    Color Color::Blue = Color::FromArgb(0xFF0000FF);
    Color Color::Black = Color::FromArgb(0x00000000);
    Color Color::White = Color::FromArgb(0xFFFFFFFF);
    Color Color::Lime = Color::FromArgb(0xFF00FF00);
}