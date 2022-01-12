#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace Borg::UI
{
    class Handle
    {
    public:
#ifdef _WIN32
        using Type = HWND;
#endif

        /**
         * @brief Default constructor.
         */
        Handle();

        ~Handle() = default;
        Handle(Handle::Type nativeHandle);
        Handle(const Handle &handle);
        Handle(Handle &&handle);

        Handle &operator=(Handle::Type nativeHandle);
        Handle &operator=(const Handle &handle);
        Handle &operator=(Handle &&handle);

        Handle::Type Get() const;
        operator Handle::Type() const;
        operator bool() const;

    private:
        Handle::Type m_Handle;
    };
}