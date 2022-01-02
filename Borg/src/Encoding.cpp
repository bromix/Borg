#include "Borg/Encoding.h"
#include "Borg/RefCast.h"
#include "Borg/String.h"
#include "Borg/CharBuffer.h"

namespace Borg
{
    template<>
    static WideCharBuffer Encoding::Convert(const WideCharBuffer &input)
    {
        return input;
    }

    template<>
    static CharBuffer Encoding::Convert(const String &input)
    {
        if (input.IsNull())
            return nullptr;

        return Encoding::Convert<CharBuffer>(input.GetBuffer());
    }

    template<>
    static WideCharBuffer Encoding::Convert(const String &input)
    {
        return Encoding::Convert<WideCharBuffer>(input.GetBuffer());
    }
}