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

TEST(DateTime, ToLocalTime)
{
    auto utcNow = DateTime::UtcNow();
    ASSERT_EQ(utcNow.Kind(), DateTimeKind::Utc);

    auto localNow = utcNow.ToLocalTime();
    ASSERT_EQ(localNow.Kind(), DateTimeKind::Local);
}

TEST(DateTime, ToUniversalTime)
{
    auto now = DateTime::Now();
    ASSERT_EQ(now.Kind(), DateTimeKind::Local);

    auto utcNow = now.ToUniversalTime();
    ASSERT_EQ(utcNow.Kind(), DateTimeKind::Utc);
}

TEST(DateTime, AddDays)
{
    auto now = DateTime::Now();
    auto days1 = now.AddDays(1);
    auto oneDayAndAHalf = now.AddDays(1.5);
    auto days3 = now.AddDays(3);
    auto negativeDays1 = now.AddDays(-1);
}