#pragma once
#include "Borg/String.h"

namespace Borg::UI::Windows
{
    class CreateParams
    {
    public:
        Borg::String ClassName;
        LONG Style = 0;
        DWORD ExStyle = 0;
        UINT ClassStyle = 0;
        int X;
        int Y;
        int Width;
        int Height;
        UI::Handle Parent;
    };
}