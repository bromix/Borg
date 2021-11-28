#include "Borg/DateTime.h"
#include <chrono>
#include <gtest/gtest.h>

using namespace Borg;

TEST(DateTime, UtcNow)
{
    auto now = DateTime::UtcNow();
    ASSERT_TRUE(true);
}
