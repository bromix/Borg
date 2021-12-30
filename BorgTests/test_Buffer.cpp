#include "Borg/Borg.h"
#include "Borg/Buffer.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(MemoryBlock, Ctr)
{
    auto size = sizeof(wchar_t);
    Buffer<wchar_t> mb = {10};
    ASSERT_EQ(10 * size, mb.Size());
    ASSERT_EQ(10, mb.Count());
}