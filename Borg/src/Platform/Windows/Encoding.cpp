#include "Borg/Encoding.h"
#include "Borg/RefCast.h"

namespace Borg
{
    CharBuffer Encoding::ToCharBuffer(const String &input)
    {
        return nullptr;
    }

    WideCharBuffer Encoding::ToWideCharBuffer(const String &input)
    {
        auto buffer = input.GetBuffer();
        if(auto result = RefAs<WideCharBuffer>(buffer))
            return std::move(*result);

        throw NotImplementedException();
    }
}