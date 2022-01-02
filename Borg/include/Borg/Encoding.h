#pragma once
#include "WideCharBuffer.h"

namespace Borg
{
    class Encoding final
    {
    public:
        Encoding() = delete;

        using Default = WideCharBuffer;

        template <typename TTo, typename TFrom>
        static TTo Convert(const TFrom &input);
    };
}