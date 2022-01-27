#pragma once
#include "BasicStringBuffer.h"

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
        using DefaultCharType = wchar_t;
#else
        using DefaultCharType = char;
#endif

        using DefaultStringBuffer = BasicStringBuffer<Encoding::DefaultCharType>;

        template <typename TTo>
        static TTo Convert(const String &input)
        {
            // TODO: do we still need this?
            // if (input.IsNull())
            //     return nullptr;
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