#include "Borg/UI/DpiHelper.h"
#include "../Windows.h"

namespace Borg::UI
{
    DpiHelper DpiHelper::FromControl(const Ref<UI::IControl>& control)
    {
        DpiHelper dpiHelper;
        dpiHelper.m_DeviceDpi = 96;

        if (!control->Handle())
            return dpiHelper;

        HMONITOR monitor = ::MonitorFromWindow(control->Handle(), MONITOR_DEFAULTTONEAREST);
        if (monitor == nullptr)
            return dpiHelper;

        UINT x, y;
        if (::GetDpiForMonitor(monitor, MDT_DEFAULT, &x, &y) == S_OK)
        {
            dpiHelper.m_DeviceDpi = x;
            return dpiHelper;
        }

        return dpiHelper;
    }

    double DpiHelper::LogicalDpi() const
    {
        return m_LogicalDpi;
    }

    int DpiHelper::DeviceDpi() const
    {
        return m_DeviceDpi;
    }

    double DpiHelper::LogicalToDeviceUnitsScalingFactor() const
    {
        return m_DeviceDpi / m_LogicalDpi;
    }
}