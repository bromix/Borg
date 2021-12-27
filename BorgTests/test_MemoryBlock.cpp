#include "Borg/Borg.h"
#include "Borg/MemoryBlock.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(MemoryBlock, Ctr)
{
    MemoryBlock<wchar_t> mb = {10};
    ASSERT_EQ(20, mb.Size());
    ASSERT_EQ(10, mb.Count());
}