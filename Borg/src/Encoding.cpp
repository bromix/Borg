#include "Borg/Encoding.h"
#include "Borg/RefCast.h"

namespace Borg
{
    CharBuffer Encoding::ToCharBuffer(const String &input)
    {
        if (input.IsNull())
            return nullptr;

        auto buffer = input.GetBuffer();
        if (Ref<CharBuffer> result = RefAs<CharBuffer>(buffer))
            return std::move(*result);

        if (Ref<WideCharBuffer> result = RefAs<WideCharBuffer>(buffer))
            return ToCharBuffer(*result);

        throw InvalidOperationException("Unknown string Encoding.");
    }

    WideCharBuffer Encoding::ToWideCharBuffer(const String &input)
    {
        auto buffer = input.GetBuffer();
        if (auto result = RefAs<WideCharBuffer>(buffer))
            return std::move(*result);

        if (Ref<CharBuffer> result = RefAs<CharBuffer>(buffer))
            return ToWideCharBuffer(*result);

        throw InvalidOperationException("Unknown string Encoding.");
    }
}