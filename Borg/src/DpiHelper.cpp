#include "Borg/UI/DpiHelper.h"
#include "Borg/Drawing/Size.h"

namespace Borg::UI
{
    template <>
    Drawing::Size DpiHelper::Scale(int deviceDpi, const Drawing::Size &value)
    {
        double scaling = deviceDpi / 96.0;
        Drawing::Size newSize = {(int32_t)(value.Width * scaling), (int32_t)(value.Height * scaling)};
        return newSize;
    }
}