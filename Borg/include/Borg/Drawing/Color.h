#pragma once
#include <cstdint>

namespace Borg::Drawing
{
    class Color
    {
    public:
        uint8_t A() const;
        uint8_t R() const;
        uint8_t G() const;
        uint8_t B() const;

        uint32_t ToArgb() const;
        uint32_t ToBgr() const;

        static Color FromArgb(uint32_t argb);
        static Color FromArgb(uint8_t r, uint8_t g, uint8_t b);

        static Color Red;
        static Color Green;
        static Color Blue;
        static Color Black;
        static Color White;
        static Color Lime;

    private:
        uint32_t m_Argb;
        uint8_t m_A;
        uint8_t m_R;
        uint8_t m_G;
        uint8_t m_B;
    };
}