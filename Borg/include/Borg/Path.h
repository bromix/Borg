#pragma once
#include "String.h"

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