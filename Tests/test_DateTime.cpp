#include "Borg/DateTime.h"
#include <chrono>
#include <gtest/gtest.h>

using namespace Borg;

TEST(DateTime, UtcNow)
{
    auto now = DateTime::UtcNow();
    ASSERT_EQ(now.Kind(), DateTimeKind::Utc);
}

TEST(DateTime, Now)
{
    auto now = DateTime::Now();
    ASSERT_EQ(now.Kind(), DateTimeKind::Local);
}
