#include "Borg/Borg.h"
#include "Borg/Buffer.h"
#include "Borg/StringBuffer.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(Buffer, SizeTest)
{
    auto count = 10;
    auto size = sizeof(wchar_t) * count;
    Buffer<wchar_t> mb = Buffer<wchar_t>::FromCount(count);
    ASSERT_EQ(size, mb.Size());
    ASSERT_EQ(count, mb.Count());
}

TEST(Buffer, Null)
{
    Buffer<wchar_t> mb = nullptr;
    ASSERT_TRUE(mb.IsNull());
    ASSERT_TRUE(mb.IsNullOrEmpty());
}

TEST(Buffer, Size0)
{
    Buffer<wchar_t> mb((std::size_t)0);
    ASSERT_TRUE(mb.IsEmpty());
    ASSERT_EQ(0, mb.Size());
    ASSERT_EQ(0, mb.Count());
}

TEST(CharBuffer, Size)
{
    auto count = 10;
    auto size = sizeof(char) * (count + 1); // +1 because of null-termination
    CharBuffer cb = CharBuffer::FromCount(count);
    ASSERT_EQ(count, cb.Count());
    ASSERT_EQ(size, cb.Size());
}

TEST(Char16Buffer, Size)
{
    auto count = 10;
    auto size = sizeof(char16_t) * (count + 1); // +1 because of null-termination
    Char16Buffer cb = Char16Buffer::FromCount(count);
    ASSERT_EQ(count, cb.Count());
    ASSERT_EQ(size, cb.Size());
}

TEST(Char32Buffer, Size)
{
    auto count = 10;
    auto size = sizeof(char32_t) * (count + 1); // +1 because of null-termination
    Char32Buffer cb = Char32Buffer::FromCount(count);
    ASSERT_EQ(count, cb.Count());
    ASSERT_EQ(size, cb.Size());
}