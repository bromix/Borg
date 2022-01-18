#pragma once
#include <cstdint>
#include "Handle.h"

namespace Borg::UI
{
    class Message
    {
    public:
#ifdef _WIN32
        using ResultType = LRESULT;

        Message(const UI::Handle &handle, UINT msg, WPARAM wParam, LPARAM lParam);

        UI::Handle Handle = nullptr;
        UINT Msg = 0;
        WPARAM WParam;
        LPARAM LParam;
        Message::ResultType Result = 0;
#else
        Message() = default;

        using Result = void;
#endif
    };
}