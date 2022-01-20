#pragma once
#include "Borg/String.h"

namespace Borg::System::IO
{
    class File final
    {
    public:
        File() = delete;

        /**
         * @brief Moves a specified file to a new location, providing the option to specify a new file name.
         * 
         * @param sourceFileName 
         * @param destFileName 
         */
        static void Move(const Borg::String &sourceFileName, const Borg::String &destFileName);
    };
}