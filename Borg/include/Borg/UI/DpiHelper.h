#pragma once
#include "IControl.h"

namespace Borg::UI
{
    class DpiHelper final
    {
    public:
        static DpiHelper FromControl(const Ref<UI::IControl>& control);

        double LogicalDpi() const;
        int DeviceDpi() const;
        double LogicalToDeviceUnitsScalingFactor() const;

        template <typename T>
        static T Scale(int deviceDpi, const T &value);

    private:
        DpiHelper() = default;
        double m_LogicalDpi = 96.0;
        int m_DeviceDpi = 96;
    };
}