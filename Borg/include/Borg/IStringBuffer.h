#pragma once

namespace Borg
{
    enum class StringEncoding
    {
        Utf8,
        Utf16,
        Utf32
    };

    class IStringBuffer
    {
    public:
        virtual ~IStringBuffer() = default;

        virtual StringEncoding Encoding() const = 0;
    };
}