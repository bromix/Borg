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

TEST(DateTime, Constructor_1982_03_09_)
{
    auto localDate = DateTime(1982, 3, 9);
    ASSERT_EQ(DateTimeKind::Local, localDate.Kind());
    ASSERT_EQ(1982, localDate.Year());
    ASSERT_EQ(3, localDate.Month());
    ASSERT_EQ(9, localDate.Day());
    ASSERT_EQ(0, localDate.Hour());
    ASSERT_EQ(0, localDate.Minute());
    ASSERT_EQ(0, localDate.Second());
    ASSERT_EQ(0, localDate.Millisecond());
    ASSERT_EQ(DayOfWeekType::Tuesday, localDate.DayOfWeek());
    ASSERT_EQ(67, localDate.DayOfYear());
}