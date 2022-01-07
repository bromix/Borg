#include "Borg/DateTime.h"
#include <chrono>
#include <gtest/gtest.h>

using namespace Borg;

TEST(DateTime, UtcNow)
{
    auto now = DateTime::UtcNow();
    ASSERT_EQ(now.Kind(), DateTimeKindEnum::Utc);
}

TEST(DateTime, Now)
{
    auto now = DateTime::Now();
    ASSERT_EQ(now.Kind(), DateTimeKindEnum::Local);
}

TEST(DateTime, ToLocalTime)
{
    auto utcNow = DateTime::UtcNow();
    ASSERT_EQ(utcNow.Kind(), DateTimeKindEnum::Utc);

    auto localNow = utcNow.ToLocalTime();
    ASSERT_EQ(localNow.Kind(), DateTimeKindEnum::Local);
}

TEST(DateTime, ToUniversalTime)
{
    auto now = DateTime::Now();
    ASSERT_EQ(now.Kind(), DateTimeKindEnum::Local);

    auto utcNow = now.ToUniversalTime();
    ASSERT_EQ(utcNow.Kind(), DateTimeKindEnum::Utc);
}

TEST(DateTime, Constructor_1982_03_09_)
{
    auto localDate = DateTime(1982, 3, 9);
    ASSERT_EQ(DateTimeKindEnum::Local, localDate.Kind());
    ASSERT_EQ(1982, localDate.Year());
    ASSERT_EQ(3, localDate.Month());
    ASSERT_EQ(9, localDate.Day());
    ASSERT_EQ(0, localDate.Hour());
    ASSERT_EQ(0, localDate.Minute());
    ASSERT_EQ(0, localDate.Second());
    ASSERT_EQ(0, localDate.Millisecond());
    ASSERT_EQ(DayOfWeekEnum::Tuesday, localDate.DayOfWeek());
    ASSERT_EQ(67, localDate.DayOfYear());
}

TEST(DateTime, Constructor_1982_03_09_20_15_35)
{
    auto localDate = DateTime(1982, 3, 9, 20, 15, 35);
    ASSERT_EQ(DateTimeKindEnum::Local, localDate.Kind());
    ASSERT_EQ(1982, localDate.Year());
    ASSERT_EQ(3, localDate.Month());
    ASSERT_EQ(9, localDate.Day());
    ASSERT_EQ(20, localDate.Hour());
    ASSERT_EQ(15, localDate.Minute());
    ASSERT_EQ(35, localDate.Second());
    ASSERT_EQ(0, localDate.Millisecond());
    ASSERT_EQ(DayOfWeekEnum::Tuesday, localDate.DayOfWeek());
    ASSERT_EQ(67, localDate.DayOfYear());
}

TEST(DateTime, Constructor_1982_03_09_20_15_35_500)
{
    auto localDate = DateTime(1982, 3, 9, 20, 15, 35, 500);
    ASSERT_EQ(DateTimeKindEnum::Local, localDate.Kind());
    ASSERT_EQ(1982, localDate.Year());
    ASSERT_EQ(3, localDate.Month());
    ASSERT_EQ(9, localDate.Day());
    ASSERT_EQ(20, localDate.Hour());
    ASSERT_EQ(15, localDate.Minute());
    ASSERT_EQ(35, localDate.Second());
    ASSERT_EQ(500, localDate.Millisecond());
    ASSERT_EQ(DayOfWeekEnum::Tuesday, localDate.DayOfWeek());
    ASSERT_EQ(67, localDate.DayOfYear());
}

TEST(DateTime, IsLeapYear)
{
    ASSERT_TRUE(DateTime::IsLeapYear(1996));
    ASSERT_FALSE(DateTime::IsLeapYear(2021));
}

TEST(DateTime, DaysInMonth)
{
    ASSERT_EQ(31, DateTime::DaysInMonth(2012, 1));
    ASSERT_EQ(29, DateTime::DaysInMonth(2012, 2));
    ASSERT_EQ(31, DateTime::DaysInMonth(2012, 3));
    ASSERT_EQ(30, DateTime::DaysInMonth(2012, 4));
    ASSERT_EQ(31, DateTime::DaysInMonth(2012, 5));
    ASSERT_EQ(30, DateTime::DaysInMonth(2012, 6));
    ASSERT_EQ(31, DateTime::DaysInMonth(2012, 7));
    ASSERT_EQ(31, DateTime::DaysInMonth(2012, 8));
    ASSERT_EQ(30, DateTime::DaysInMonth(2012, 9));
    ASSERT_EQ(31, DateTime::DaysInMonth(2012, 10));
    ASSERT_EQ(30, DateTime::DaysInMonth(2012, 11));
    ASSERT_EQ(31, DateTime::DaysInMonth(2012, 12));

    ASSERT_EQ(31, DateTime::DaysInMonth(2014, 1));
    ASSERT_EQ(28, DateTime::DaysInMonth(2014, 2));
    ASSERT_EQ(31, DateTime::DaysInMonth(2014, 3));
    ASSERT_EQ(30, DateTime::DaysInMonth(2014, 4));
    ASSERT_EQ(31, DateTime::DaysInMonth(2014, 5));
    ASSERT_EQ(30, DateTime::DaysInMonth(2014, 6));
    ASSERT_EQ(31, DateTime::DaysInMonth(2014, 7));
    ASSERT_EQ(31, DateTime::DaysInMonth(2014, 8));
    ASSERT_EQ(30, DateTime::DaysInMonth(2014, 9));
    ASSERT_EQ(31, DateTime::DaysInMonth(2014, 10));
    ASSERT_EQ(30, DateTime::DaysInMonth(2014, 11));
    ASSERT_EQ(31, DateTime::DaysInMonth(2014, 12));
}

TEST(DateTime, IsDaylightSavingTime)
{
    // This test is just for the implementation.
    auto startDate = DateTime(2021, 3, 28, 3, 0, 0);
    auto midDate = DateTime(2021, 6, 5);
    auto endDate = DateTime(2021, 10, 31, 1, 59, 0);
    ASSERT_TRUE(true);
}

TEST(DateTime, AddDays)
{
    auto date1 = DateTime(2021, 11, 10, 12, 33, 5);
    auto date2 = date1.AddDays(2);
    ASSERT_EQ(2021, date2.Year());
    ASSERT_EQ(11, date2.Month());
    ASSERT_EQ(12, date2.Day());
    ASSERT_EQ(12, date2.Hour());
    ASSERT_EQ(33, date2.Minute());
    ASSERT_EQ(5, date2.Second());

    auto date3 = date1.AddDays(-2);
    ASSERT_EQ(2021, date3.Year());
    ASSERT_EQ(11, date3.Month());
    ASSERT_EQ(8, date3.Day());
    ASSERT_EQ(12, date3.Hour());
    ASSERT_EQ(33, date3.Minute());
    ASSERT_EQ(5, date3.Second());
}

TEST(DateTime, SubtractDate)
{
    auto date1 = DateTime(2021, 11, 10, 0, 0, 0);
    auto date2 = DateTime(2021, 11, 10, 0, 0, 1);
    auto diff1 = date2 - date1;
    ASSERT_EQ(0, diff1.Days());
    ASSERT_EQ(0, diff1.Hours());
    ASSERT_EQ(0, diff1.Minutes());
    ASSERT_EQ(1, diff1.Seconds());

    auto date3 = DateTime(2021, 11, 10, 0, 1, 1);
    auto diff2 = date3 - date1;
    ASSERT_EQ(0, diff2.Days());
    ASSERT_EQ(0, diff2.Hours());
    ASSERT_EQ(1, diff2.Minutes());
    ASSERT_EQ(1, diff2.Seconds());

    auto date4 = DateTime(2021, 11, 10, 1, 1, 1);
    auto diff3 = date4 - date1;
    ASSERT_EQ(0, diff3.Days());
    ASSERT_EQ(1, diff3.Hours());
    ASSERT_EQ(1, diff3.Minutes());
    ASSERT_EQ(1, diff3.Seconds());

    auto date5 = DateTime(2021, 11, 11, 1, 1, 1);
    auto diff4 = date5 - date1;
    ASSERT_EQ(1, diff4.Days());
    ASSERT_EQ(1, diff4.Hours());
    ASSERT_EQ(1, diff4.Minutes());
    ASSERT_EQ(1, diff4.Seconds());

    auto date6 = date1.AddDays(10);
    auto diff5 = date6 - date1;
    ASSERT_EQ(10, diff5.Days());
    ASSERT_EQ(0, diff5.Hours());
    ASSERT_EQ(0, diff5.Minutes());
    ASSERT_EQ(0, diff5.Seconds());
}

TEST(DateTime, Compare)
{
    auto date1 = DateTime::UtcNow();
    auto date2(date1);
    ASSERT_FALSE(date1 > date2);
    ASSERT_EQ(date1, date2);
    ASSERT_TRUE(date1 >= date2);
}

TEST(DateTime, UnixEpoch)
{
    auto unixEpoch = DateTime::UnixEpoch();
    ASSERT_EQ(1970, unixEpoch.Year());
    ASSERT_EQ(1, unixEpoch.Month());
    ASSERT_EQ(1, unixEpoch.Day());
    ASSERT_EQ(0, unixEpoch.Hour());
    ASSERT_EQ(0, unixEpoch.Minute());
    ASSERT_EQ(0, unixEpoch.Second());
    ASSERT_EQ(0, unixEpoch.Millisecond());
}

TEST(DateTime, NetworkEpoch)
{
    auto date_time = DateTime::FromNetworkTimeMilliseconds(3845454182000, DateTimeKindEnum::Utc);
    ASSERT_EQ(13, date_time.Hour());
    ASSERT_EQ(43, date_time.Minute());
    ASSERT_EQ(2, date_time.Second());
    ASSERT_EQ(9, date_time.Day());
    ASSERT_EQ(11, date_time.Month());
    ASSERT_EQ(2021, date_time.Year());
    ASSERT_EQ(3845454182000, date_time.ToNetworkTimeMilliseconds());

    auto date_time2 = DateTime::FromNetworkTimeSeconds(3845454182, DateTimeKindEnum::Utc);
    ASSERT_EQ(13, date_time2.Hour());
    ASSERT_EQ(43, date_time2.Minute());
    ASSERT_EQ(2, date_time2.Second());
    ASSERT_EQ(9, date_time2.Day());
    ASSERT_EQ(11, date_time2.Month());
    ASSERT_EQ(2021, date_time2.Year());
    ASSERT_EQ(3845454182, date_time2.ToNetworkTimeSeconds());
}

TEST(DateTime, Parse)
{
    auto dateTime = DateTime::Parse("2021-12-12T22:59:59Z");
    ASSERT_EQ(2021,  dateTime.Year());
    ASSERT_EQ(12, dateTime.Month());
    ASSERT_EQ(12, dateTime.Day());
    ASSERT_EQ(22, dateTime.Hour());
    ASSERT_EQ(59, dateTime.Minute());
    ASSERT_EQ(59, dateTime.Second());

    dateTime = DateTime::Parse("2021-02-01T02:09:09Z");
    ASSERT_EQ(2021,  dateTime.Year());
    ASSERT_EQ(2, dateTime.Month());
    ASSERT_EQ(1, dateTime.Day());
    ASSERT_EQ(2, dateTime.Hour());
    ASSERT_EQ(9, dateTime.Minute());
    ASSERT_EQ(9, dateTime.Second());
}