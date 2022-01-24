#include "Borg/Screen.h"
#include <vector>

namespace Borg
{
    static BOOL CALLBACK MonitorEnumProc(HMONITOR hMon, HDC hdc, LPRECT lprcMonitor, LPARAM pData)
    {
        std::vector<HMONITOR> *monitorList = reinterpret_cast<std::vector<HMONITOR> *>(pData);
        monitorList->push_back(hMon);
        return TRUE;
    }

    std::vector<HMONITOR> getMonitors()
    {
        std::vector<HMONITOR> result;
        ::EnumDisplayMonitors(nullptr, nullptr, &MonitorEnumProc, (LPARAM)&result);
        return result;
    }

    Screen Screen::PrimaryScreen()
    {
        auto monitors = getMonitors();

        for (auto monitor : monitors)
        {
            MONITORINFOEXW monitorinfoex{};
            monitorinfoex.cbSize = sizeof(MONITORINFOEXW);
            if (::GetMonitorInfoW(monitor, &monitorinfoex) != TRUE)
                throw InvalidOperationException("Failed to get monitor information.");
            bool isPrimary = (monitorinfoex.dwFlags & MONITORINFOF_PRIMARY);
            if (isPrimary)
            {
                Screen screen;
                screen.m_IsPrimary = isPrimary;
                screen.m_DeviceName = monitorinfoex.szDevice;
                screen.m_Bounds = {monitorinfoex.rcMonitor.left, monitorinfoex.rcMonitor.top, monitorinfoex.rcMonitor.right, monitorinfoex.rcMonitor.bottom};
                screen.m_WorkingArea = {monitorinfoex.rcWork.left, monitorinfoex.rcWork.top, monitorinfoex.rcWork.right, monitorinfoex.rcWork.bottom};
                return screen;
            }
        }

        throw InvalidOperationException("Failed to get primary monitor.");
    }

    Screen Screen::FromControl(const UI::IControl &control)
    {
        return Screen::FromHandle(control.Handle());
    }

    Screen Screen::FromHandle(const UI::Handle &handle)
    {
        HMONITOR hMonitor = ::MonitorFromWindow(handle, MONITOR_DEFAULTTONEAREST);
        if (hMonitor == nullptr)
            throw InvalidOperationException("MonitorFromWindow failed");

        throw InvalidOperationException("Failed to get monitor from handle.");
    }
}