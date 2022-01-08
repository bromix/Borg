#pragma once
#include "CharBuffer.h"
#include "WideCharBuffer.h"

namespace Borg
{
    class String;
    class Encoding final
    {
    private:
        template <typename TTo, typename TFrom>
        using IsSameEncodingType = std::enable_if_t<std::is_same_v<TTo, TFrom>, bool>;

        template <typename TTo, typename TFrom>
        using IsNotSameEncodingType = std::enable_if_t<!std::is_same_v<TTo, TFrom>, bool>;

    public:
        Encoding() = delete;

#ifdef _WIN32
        using DefaultChar = wchar_t;
        using Default = WideCharBuffer;
#else
        using DefaultChar = char;
        using Default = CharBuffer;
#endif

        template <typename TTo>
        static TTo Convert(const String &input)
        {
            if (input.IsNull())
                return nullptr;
            return Convert<TTo>(input.GetBuffer());
        }

        template <typename TTo, typename TFrom, IsNotSameEncodingType<TTo, TFrom> = true>
        static TTo Convert(const TFrom &input);

        template <typename TTo, typename TFrom, IsSameEncodingType<TTo, TFrom> = true>
        static TTo Convert(TFrom input)
        {
            return input;
        }
    };
}