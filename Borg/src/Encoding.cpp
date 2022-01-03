#include "Borg/Encoding.h"
#include "Borg/RefCast.h"
#include "Borg/String.h"
#include "Borg/CharBuffer.h"
#include "Borg/WideCharBuffer.h"

namespace Borg
{
    // template<>
    // static CharBuffer Encoding::ConvertTo<CharBuffer, String>(const String &input)
    // {
    //     if (input.IsNull())
    //         return nullptr;

    //     return Encoding::ConvertTo<CharBuffer, Encoding::Default>(input.GetBuffer());
    // }

    // template<>
    // static WideCharBuffer Encoding::ConvertTo<WideCharBuffer, String>(const String &input)
    // {
    //     return Encoding::ConvertTo<WideCharBuffer, Encoding::Default>(input.GetBuffer());
    // }
}