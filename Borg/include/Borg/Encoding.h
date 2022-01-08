#pragma once
#include "CharBuffer.h"
#include "WideCharBuffer.h"

namespace Borg
{
    class String;
    class Encoding final
    {
    public:
        Encoding() = delete;

#ifdef _WIN32
        using DefaultChar = wchar_t;
        using Default = WideCharBuffer;
#else
        using DefaultChar = char;
        using Default = CharBuffer;
#endif

        template <typename TTo, typename TFrom>
        using IsSameEncodingType = std::enable_if_t<std::is_same_v<TTo, TFrom>, bool>;

        template <typename TTo, typename TFrom>
        using IsNotSameEncodingType = std::enable_if_t<!std::is_same_v<TTo, TFrom>, bool>;

        template <typename TTo, typename TFrom, IsNotSameEncodingType<TTo, TFrom> = true>
        static TTo ConvertTo(const TFrom &input);

        template <typename TTo>
        static TTo ConvertTo(const String &input)
        {
            if (input.IsNull())
                return nullptr;
            return ConvertTo<TTo, Encoding::Default>(input.GetBuffer());
        }

        template <typename TTo, typename TFrom, IsSameEncodingType<TTo, TFrom> = true>
        static TTo ConvertTo(TFrom input)
        {
            return input;
        }
    };
}