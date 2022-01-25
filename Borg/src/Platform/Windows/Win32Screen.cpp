#include "Win32Screen.h"
#include "Windows.h"
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

    List<Screen> Screen::GetAllScreens()
    {
        List<Screen> screens{};

        auto monitors = getMonitors();

        for (auto monitor : monitors)
        {
            Screen screen = Win32::Screen::FromHMonitor(monitor);
            screens.Add(screen);
        }

        return screens;
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

        return Win32::Screen::FromHMonitor(hMonitor);
    }

    Screen Win32::Screen::FromHMonitor(HMONITOR monitor)
    {
        MONITORINFOEXW monitorinfoex{};
        monitorinfoex.cbSize = sizeof(MONITORINFOEXW);

        if (::GetMonitorInfoW(monitor, &monitorinfoex) != TRUE)
            throw InvalidOperationException("Failed to get monitor information.");
        return Win32::Screen::FromMonitorInfo(monitorinfoex);
    }

    Screen Win32::Screen::FromMonitorInfo(const MONITORINFOEXW &monitorInfo)
    {
        Screen screen;
        screen.m_IsPrimary = monitorInfo.dwFlags & MONITORINFOF_PRIMARY;
        screen.m_DeviceName = monitorInfo.szDevice;
        screen.m_Bounds = {monitorInfo.rcMonitor.left, monitorInfo.rcMonitor.top, monitorInfo.rcMonitor.right, monitorInfo.rcMonitor.bottom};
        screen.m_WorkingArea = {monitorInfo.rcWork.left, monitorInfo.rcWork.top, monitorInfo.rcWork.right, monitorInfo.rcWork.bottom};
        return screen;
    }
}