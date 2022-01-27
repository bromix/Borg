#pragma once
#include "String.h"

#ifdef _WIN32
/*
To avoid conflicts with the defines of Windows, we have
undefine some of the windows functions. These functions
only forward functions for ANSI or UNICODE.

For example:
#define GetTempFileName  GetTempFileNameW
*/
#undef GetTempPath
#undef GetTempFileName
#endif

namespace Borg
{
    class Path final
    {
    public:
        Path() = delete;

        /**
         * @brief Get the Temp Path objectReturns the path of the current user's temporary folder.
         *
         * @return Borg::String
         */
        static Borg::String GetTempPath();

        /**
         * @brief Get the Temp File Name objectCreates a uniquely named, zero-byte temporary file on disk and returns the full path of that file.
         *
         * @return Borg::String
         */
        static Borg::String GetTempFileName();
    };
}