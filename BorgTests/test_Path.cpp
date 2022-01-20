#include "Borg/Path.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(Path, GetTempFileName)
{
    auto tempFileName = Path::GetTempFileName();
    ASSERT_TRUE(tempFileName);
}
