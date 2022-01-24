#pragma once
#include "Borg/Screen.h"

namespace Borg::Win32
{
    class Screen : public Borg::Screen
    {
    public:
        static Borg::Screen FromHMonitor(HMONITOR monitor);
        static Borg::Screen FromMonitorInfo(const MONITORINFOEXW &monitorInfo);
    };
}