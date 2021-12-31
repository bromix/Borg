#include "Borg/Borg.h"
#include "Borg/StringBuffer.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(CharBuffer, Size)
{
    auto count = 10;
    auto size = sizeof(char) * (count + 1); // +1 because of null-termination
    CharBuffer cb = CharBuffer(count);
    ASSERT_EQ(count, cb.Length());
    ASSERT_EQ(size, cb.ByteLength());
}

TEST(Char16Buffer, Size)
{
    auto count = 10;
    auto size = sizeof(char16_t) * (count + 1); // +1 because of null-termination
    Char16Buffer cb = Char16Buffer(count);
    ASSERT_EQ(count, cb.Length());
    ASSERT_EQ(size, cb.ByteLength());
}

TEST(Char32Buffer, Size)
{
    auto count = 10;
    auto size = sizeof(char32_t) * (count + 1); // +1 because of null-termination
    Char32Buffer cb = Char32Buffer(count);
    ASSERT_EQ(count, cb.Length());
    ASSERT_EQ(size, cb.ByteLength());
}