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

        template <typename TTo, typename TFrom>
        static TTo ConvertTo(const TFrom &input);

        template <typename TTo>
        static TTo ConvertTo(const String &input)
        {
            if(input.IsNull())
                return nullptr;
            return ConvertTo<TTo, Encoding::Default>(input.GetBuffer());
        }

        template<>
        static WideCharBuffer ConvertTo<WideCharBuffer, WideCharBuffer>(const WideCharBuffer& input)
        {
            return input;
        }
    };
}