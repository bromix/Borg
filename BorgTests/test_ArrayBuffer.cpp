#include "Borg/ArrayBuffer.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(ArrayBuffer, Empty)
{
    ArrayBuffer<wchar_t> ab;
    ASSERT_EQ(0, ab.GetCapacity());
    ASSERT_TRUE(ab.IsEmpty());
}

TEST(ArrayBuffer, IsDetached)
{
    ArrayBuffer<wchar_t> ab;
    auto detached = ab.Detach();
    ASSERT_TRUE(ab.IsDetached());
    ASSERT_TRUE(detached.IsDetached());
}
