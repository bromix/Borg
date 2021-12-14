#pragma once
#include "Borg.h"

namespace Borg
{
    class Environment final
    {
    public:
        enum class SpecialFolder
        {
            ApplicationData,
            LocalApplicationData
        };

        Environment() = delete;

        static String GetFolderPath(SpecialFolder specialFolder);
    };
}