#pragma once
#include "WideCharBuffer.h"

namespace Borg
{
    class String;
    class Encoding final
    {
    public:
        Encoding() = delete;

        using Default = WideCharBuffer;

        template <typename TTo, typename TFrom, typename std::enable_if_t<!std::is_same<TTo, TFrom>::value>* = nullptr>
        static TTo ConvertTo(const TFrom &input);

        template <typename TTo>
        static TTo ConvertTo(const String &input)
        {
            if(input.IsNull())
                return nullptr;
            return ConvertTo<TTo, Encoding::Default>(input.GetBuffer());
        }

        template<typename TTo, typename TFrom, typename std::enable_if_t<std::is_same<TTo, TFrom>::value>* = nullptr>
        static TTo ConvertTo(const TFrom& input)
        {
            return input;
        }

        template<typename TTo, typename TFrom, typename std::enable_if_t<std::is_same<TTo, TFrom>::value>* = nullptr>
        static TTo ConvertTo(TFrom&& input)
        {
            return input;
        }
    };
}