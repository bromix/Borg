#pragma once
#include "StringBuffer.h"

namespace Borg
{
    class String;
    class Encoding final
    {
    public:
        Encoding() = delete;

        static CharBuffer ToCharBuffer(const WideCharBuffer &input);
        static CharBuffer ToCharBuffer(const String &input);

        static WideCharBuffer ToWideCharBuffer(const CharBuffer &input);
        static WideCharBuffer ToWideCharBuffer(const String &input);
    };
}