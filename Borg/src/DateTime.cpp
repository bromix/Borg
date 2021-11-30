#include "Borg/DateTime.h"
#include <chrono>
#include <cmath>
#include <exception>

namespace Borg
{
    // ================
    // === DateTime ===
    // ================

    DateTime::DateTime()
    {
    }

    DateTime DateTime::UtcNow()
    {
        using namespace std::chrono;
        auto now = system_clock::now().time_since_epoch();
        auto millisecondsSinceEpoch = duration_cast<milliseconds>(now).count();

        return FromUnixEpochMilliseconds(millisecondsSinceEpoch, DateTimeKindEnum::Utc);
    }

    DateTime DateTime::Now()
    {
        using namespace std::chrono;
        auto now = system_clock::now().time_since_epoch();
        auto millisecondsSinceEpoch = duration_cast<milliseconds>(now).count();

        return FromUnixEpochMilliseconds(millisecondsSinceEpoch, DateTimeKindEnum::Local);
    }

    DateTime DateTime::FromUnixEpochSeconds(uint64 secondsSinceEpoch, DateTimeKindEnum kind)
    {
        return FromUnixEpochMilliseconds(secondsSinceEpoch * 1000, kind);
    }

    DateTime DateTime::FromUnixEpochMilliseconds(uint64 millisecondsSinceEpoch, DateTimeKindEnum kind)
    {
        uint32 milliseconds = millisecondsSinceEpoch % 1000;
        int64 secondsSinceEpoch = millisecondsSinceEpoch / 1000;

        std::tm tm = {};
        if (kind == DateTimeKindEnum::Local)
            localtime_s(&tm, &secondsSinceEpoch);
        else
            gmtime_s(&tm, &secondsSinceEpoch);

        DateTime dt{};
        dt.m_Year = tm.tm_year + 1900;
        dt.m_Month = tm.tm_mon + 1;
        dt.m_Day = tm.tm_mday;
        dt.m_Hour = tm.tm_hour;
        dt.m_Minute = tm.tm_min;
        dt.m_Second = tm.tm_sec;
        dt.m_Millisecond = milliseconds;
        dt.m_DayOfYear = tm.tm_yday;
        dt.m_DayOfWeek = static_cast<DayOfWeekEnum>(tm.tm_wday);
        dt.m_UnixEpochMilliseconds = millisecondsSinceEpoch;
        dt.m_Kind = kind;
        dt.m_IsDaylightSavingTime = kind == DateTimeKindEnum::Local && tm.tm_isdst != 0;

        return dt;
    }

    uint32 DateTime::DaysInMonth(uint32 year, uint32 month)
    {
        switch (month)
        {
        case 1:  // January
        case 3:  // March
        case 5:  // May
        case 7:  // July
        case 8:  // August
        case 10: // October
        case 12: // December
            return 31;
        case 2: // February
            return IsLeapYear(year) ? 29 : 28;
        case 4:  // April
        case 6:  // June
        case 9:  // September
        case 11: // November
            return 30;
        }

        // TODO: ArgumentOutOfRangeException
        throw std::exception("ArgumentOutOfRangeException");
    }

    bool DateTime::IsLeapYear(uint32 year)
    {
        return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    }

    DateTime::DateTime(uint32 year, uint32 month, uint32 day, DateTimeKindEnum kind)
        : DateTime(year, month, day, 0, 0, 0, 0, kind)
    {
    }

    DateTime::DateTime(uint32 year, uint32 month, uint32 day, uint32 hour, uint32 minute, uint32 second, DateTimeKindEnum kind)
        : DateTime(year, month, day, hour, minute, second, 0, kind)
    {
    }

    DateTime::DateTime(uint32 year, uint32 month, uint32 day, uint32 hour, uint32 minute, uint32 second, uint32 millisecond, DateTimeKindEnum kind)
    {
        std::tm tm = {0};
        tm.tm_year = year - 1900;
        tm.tm_mon = month - 1;
        tm.tm_mday = day;
        tm.tm_hour = hour;
        tm.tm_min = minute;
        tm.tm_sec = second;
        tm.tm_isdst = -1;

        auto time = std::mktime(&tm);
        auto timePoint = std::chrono::system_clock::from_time_t(time).time_since_epoch();
        auto chronoMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint).count();

        // Because std::tm only support seconds we must add the given milliseconds.
        auto newDate = FromUnixEpochMilliseconds(chronoMilliseconds + millisecond, kind);

        // Assign members from newDate to this and we're done.
        *this = newDate;
    }

    DateTime DateTime::ToLocalTime() const
    {
        if (m_Kind == DateTimeKindEnum::Local)
            return *this;

        return FromUnixEpochMilliseconds(m_UnixEpochMilliseconds, DateTimeKindEnum::Local);
    }

    DateTime DateTime::ToUniversalTime() const
    {
        if (m_Kind == DateTimeKindEnum::Utc)
            return *this;

        return FromUnixEpochMilliseconds(m_UnixEpochMilliseconds, DateTimeKindEnum::Utc);
    }

    DateTime DateTime::Add(const TimeSpan &timespan) const
    {
        return AddMilliseconds(timespan.TotalMilliseconds());
    }

    TimeSpan DateTime::Subtract(const DateTime &datetime) const
    {
        if (m_Kind == DateTimeKindEnum::Utc)
        {
            auto utcDiff = m_UnixEpochMilliseconds - datetime.ToUniversalTime().m_UnixEpochMilliseconds;
            return TimeSpan::FromMilliseconds(utcDiff);
        }

        auto localDiff = m_UnixEpochMilliseconds - datetime.ToLocalTime().m_UnixEpochMilliseconds;
        return TimeSpan::FromMilliseconds(localDiff);
    }

    DateTime DateTime::Subtract(const TimeSpan &timespan) const
    {
        return FromUnixEpochMilliseconds(m_UnixEpochMilliseconds - timespan.TotalMilliseconds(), m_Kind);
    }

    DateTime DateTime::AddDays(double days) const
    {
        return AddHours(days * 24.0);
    }

    DateTime DateTime::AddHours(double hours) const
    {
        return AddMinutes(hours * 60.0);
    }

    DateTime DateTime::AddMinutes(double minutes) const
    {
        return AddSeconds(minutes * 60.0);
    }

    DateTime DateTime::AddSeconds(double seconds) const
    {
        return AddMilliseconds(seconds * 1000.0);
    }

    DateTime DateTime::AddMilliseconds(double milliseconds) const
    {
        if (m_Kind != DateTimeKindEnum::Utc)
            return ToUniversalTime().AddMilliseconds(milliseconds).ToLocalTime();

        return FromUnixEpochMilliseconds(m_UnixEpochMilliseconds + std::llround(milliseconds), m_Kind);
    }

    uint32 DateTime::Year() const
    {
        return m_Year;
    }

    uint32 DateTime::Month() const
    {
        return m_Month;
    }

    uint32 DateTime::Day() const
    {
        return m_Day;
    }

    uint32 DateTime::Hour() const
    {
        return m_Hour;
    }

    uint32 DateTime::Minute() const
    {
        return m_Minute;
    }

    uint32 DateTime::Second() const
    {
        return m_Second;
    }

    uint32 DateTime::Millisecond() const
    {
        return m_Millisecond;
    }

    uint32 DateTime::DayOfYear() const
    {
        return m_DayOfYear;
    }

    DayOfWeekEnum DateTime::DayOfWeek() const
    {
        return m_DayOfWeek;
    }

    DateTimeKindEnum DateTime::Kind() const
    {
        return m_Kind;
    }

    bool DateTime::IsDaylightSavingTime() const
    {
        return m_IsDaylightSavingTime;
    }

    DateTime DateTime::operator+(const TimeSpan &timespan)
    {
        return Add(timespan);
    }

    TimeSpan DateTime::operator-(const DateTime &rhs)
    {
        return Subtract(rhs);
    }

    DateTime DateTime::operator-(const TimeSpan &timespan)
    {
        return Subtract(timespan);
    }

    // ================
    // === TimeSpan ===
    // ================

    TimeSpan TimeSpan::FromDays(double days)
    {
        return FromHours(days * 24.0);
    }

    TimeSpan TimeSpan::FromHours(double hours)
    {
        return FromMinutes(hours * 60.0);
    }

    TimeSpan TimeSpan::FromMinutes(double minutes)
    {
        return FromSeconds(minutes * 60.0);
    }

    TimeSpan TimeSpan::FromSeconds(double seconds)
    {
        return FromMilliseconds(seconds * 1000.0);
    }

    TimeSpan TimeSpan::FromMilliseconds(double milliseconds)
    {
        auto totalMilliseconds = milliseconds;
        auto totalSeconds = totalMilliseconds / 1000.0;
        auto totalMinutes = totalSeconds / 60.0;
        auto totalHours = totalMinutes / 60.0;
        auto totalDays = totalHours / 24.0;

        auto ms = (int)totalMilliseconds % 1000;
        auto seconds = (int)totalSeconds % 60;
        auto minutes = (int)totalMinutes % 60;
        auto hours = (int)totalHours % 24;
        auto days = (int)totalDays % 24;

        return TimeSpan(days, hours, minutes, seconds, ms);
    }

    TimeSpan::TimeSpan(int32 hours, int32 minutes, int32 seconds)
        : TimeSpan(0, hours, minutes, seconds, 0)
    {
    }

    TimeSpan::TimeSpan(int32 days, int32 hours, int32 minutes, int32 seconds)
        : TimeSpan(days, hours, minutes, seconds, 0)
    {
    }

    TimeSpan::TimeSpan(int32 days, int32 hours, int32 minutes, int32 seconds, int32 milliseconds)
        : m_Days(days), m_Hours(hours), m_Minutes(minutes), m_Seconds(seconds), m_Milliseconds(milliseconds)
    {
        auto ms =
            m_Milliseconds +
            m_Seconds * 1000 +
            m_Minutes * 1000 * 60 +
            m_Hours * 1000 * 60 * 60 +
            m_Days * 1000 * 60 * 60 * 24;

        m_TotalMilliseconds = (double)ms;
        m_TotalSeconds = m_TotalMilliseconds / 1000.0;
        m_TotalMinutes = m_TotalSeconds / 60.0;
        m_TotalHours = m_TotalMinutes / 60.0;
        m_TotalDays = m_TotalHours / 24.0;
    }

    TimeSpan TimeSpan::Add(const TimeSpan &timespan) const
    {
        return FromMilliseconds(m_TotalMilliseconds + timespan.m_TotalMilliseconds);
    }

    TimeSpan TimeSpan::Subtract(const TimeSpan &timespan) const
    {
        return FromMilliseconds(m_TotalMilliseconds - timespan.m_TotalMilliseconds);
    }

    int32 TimeSpan::Days() const
    {
        return m_Days;
    }

    double TimeSpan::TotalDays() const
    {
        return m_TotalDays;
    }

    int32 TimeSpan::Hours() const
    {
        return m_Hours;
    }

    double TimeSpan::TotalHours() const
    {
        return m_TotalHours;
    }

    int32 TimeSpan::Minutes() const
    {
        return m_Minutes;
    }

    double TimeSpan::TotalMinutes() const
    {
        return m_TotalMinutes;
    }

    int32 TimeSpan::Seconds() const
    {
        return m_Seconds;
    }

    double TimeSpan::TotalSeconds() const
    {
        return m_TotalSeconds;
    }

    int32 TimeSpan::Milliseconds() const
    {
        return m_Milliseconds;
    }

    double TimeSpan::TotalMilliseconds() const
    {
        return m_TotalMilliseconds;
    }

    TimeSpan TimeSpan::operator+(const TimeSpan &timespan)
    {
        return Add(timespan);
    }

    TimeSpan TimeSpan::operator-(const TimeSpan &timespan)
    {
        return Subtract(timespan);
    }
}