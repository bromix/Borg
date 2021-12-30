#pragma once
#include "StringBuffer.h"

namespace Borg
{
    class Encoding final
    {
    public:
        Encoding() = delete;

        static CharBuffer ToCharBuffer(const String &input);
        static WideCharBuffer ToWideCharBuffer(const String &input);
    };
}