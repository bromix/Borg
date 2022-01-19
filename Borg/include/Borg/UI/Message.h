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

        const UI::Handle Handle = nullptr;
        const UINT Msg = 0;
        const WPARAM WParam;
        const LPARAM LParam;
        Message::ResultType Result;
#else
        using ResultType = void;
        Message() = default;
#endif
    };
}