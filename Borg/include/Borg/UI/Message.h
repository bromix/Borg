#pragma once
#include <cstdint>
#include "Handle.h"

namespace Borg::UI
{
    class Message
    {
    public:
#ifdef _WIN32
        Message(const UI::Handle &handle, UINT msg, WPARAM wParam, LPARAM lParam);

        UI::Handle Handle = nullptr;
        UINT Msg = 0;
        WPARAM WParam;
        LPARAM LParam;

        using Result = LRESULT;
#else
        Message() = default;

        using Result = void;
#endif
    };
}