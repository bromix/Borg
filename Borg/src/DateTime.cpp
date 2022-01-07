#include "Borg/DateTime.h"
#include "Borg/Exception.h"
#include <chrono>
#include <cmath>

namespace Borg
{
    class YearArgumentOutOfRangeException : public ArgumentOutOfRangeException
    {
    public:
        YearArgumentOutOfRangeException() : YearArgumentOutOfRangeException("year") {}
        YearArgumentOutOfRangeException(const String &paramName) : ArgumentOutOfRangeException(paramName, "year is less than 1 or greater than 9999.") {}
    };

    class MonthArgumentOutOfRangeException : public ArgumentOutOfRangeException
    {
    public:
        MonthArgumentOutOfRangeException() : MonthArgumentOutOfRangeException("month") {}
        MonthArgumentOutOfRangeException(const String &paramName) : ArgumentOutOfRangeException(paramName, "month is less than 1 or greater than 12.") {}
    };

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

        return FromUnixEpochMilliseconds(millisecondsSinceEpoch, DateTimeKind::Utc);
    }

    DateTime DateTime::Now()
    {
        using namespace std::chrono;
        auto now = system_clock::now().time_since_epoch();
        auto millisecondsSinceEpoch = duration_cast<milliseconds>(now).count();

        return FromUnixEpochMilliseconds(millisecondsSinceEpoch, DateTimeKind::Local);
    }

    DateTime DateTime::FromUnixEpochSeconds(uint64_t secondsSinceEpoch, DateTimeKind kind)
    {
        return FromUnixEpochMilliseconds(secondsSinceEpoch * 1000, kind);
    }

    DateTime DateTime::FromUnixEpochMilliseconds(uint64_t millisecondsSinceEpoch, DateTimeKind kind)
    {
        if (millisecondsSinceEpoch < 0)
            throw ArgumentOutOfRangeException("millisecondsSinceEpoch", "value is less than 0 or represents a time greater than MaxValue.");

        uint32_t milliseconds = millisecondsSinceEpoch % 1000;
        int64_t secondsSinceEpoch = millisecondsSinceEpoch / 1000;

        std::tm tm = {};
        if (kind == DateTimeKind::Local)
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
        dt.m_IsDaylightSavingTime = kind == DateTimeKind::Local && tm.tm_isdst != 0;

        return dt;
    }

    DateTime DateTime::FromNetworkTimeSeconds(uint64_t secondsSinceEpoch, DateTimeKind kind)
    {
        return FromNetworkTimeMilliseconds(secondsSinceEpoch * 1000, kind);
    }

    DateTime DateTime::FromNetworkTimeMilliseconds(uint64_t millisecondsSinceEpoch, DateTimeKind kind)
    {
        /*
        Subtract 70 years from NetworkTime to get UNIX epoch.
        https://datatracker.ietf.org/doc/html/rfc868
        */
        return FromUnixEpochMilliseconds(millisecondsSinceEpoch - 2208988800000, kind);
    }

    uint64_t DateTime::ToNetworkTimeSeconds() const
    {
        return ToNetworkTimeMilliseconds() / 1000.0;
    }

    uint64_t DateTime::ToNetworkTimeMilliseconds() const
    {
        /*
        Add 70 years to UNIX epoch to get NetworkTime.
        https://datatracker.ietf.org/doc/html/rfc868
        */
        return m_UnixEpochMilliseconds + 2208988800000;
    }

    uint32_t DateTime::DaysInMonth(uint32_t year, uint32_t month)
    {
        if (year < 1 || year > 9999)
            throw YearArgumentOutOfRangeException();

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

        throw MonthArgumentOutOfRangeException();
    }

    bool DateTime::IsLeapYear(uint32_t year)
    {
        if (year < 1 || year > 9999)
            throw YearArgumentOutOfRangeException();

        return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    }

    DateTime::DateTime(uint32_t year, uint32_t month, uint32_t day, DateTimeKind kind)
        : DateTime(year, month, day, 0, 0, 0, 0, kind)
    {
    }

    DateTime::DateTime(uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second, DateTimeKind kind)
        : DateTime(year, month, day, hour, minute, second, 0, kind)
    {
    }

    DateTime::DateTime(uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second, uint32_t millisecond, DateTimeKind kind)
    {
        if (year < 1 || year > 9999)
            throw YearArgumentOutOfRangeException();

        if (month < 1 || month > 12)
            throw MonthArgumentOutOfRangeException();

        if (day < 1 || day > DaysInMonth(year, month))
            throw ArgumentOutOfRangeException("day", "day is less than 1 or greater than the number of days in month.");

        if (hour < 0 || hour > 23)
            throw ArgumentOutOfRangeException("hour", "hour is less than 0 or greater than 23.");

        if (minute < 0 || minute > 59)
            throw ArgumentOutOfRangeException("minute", "minute is less than 0 or greater than 59.");

        if (second < 0 || second > 59)
            throw ArgumentOutOfRangeException("second", "second is less than 0 or greater than 59.");

        if (millisecond < 0 || millisecond > 999)
            throw ArgumentOutOfRangeException("millisecond", "millisecond is less than 0 or greater than 999.");

        std::tm tm = {0};
        tm.tm_year = year - 1900;
        tm.tm_mon = month - 1;
        tm.tm_mday = day;
        tm.tm_hour = hour;
        tm.tm_min = minute;
        tm.tm_sec = second;
        tm.tm_isdst = -1;

        auto time = std::mktime(&tm);
        if (time < 0)
            throw InvalidOperationException("std::mktime returned -1");

        auto timePoint = std::chrono::system_clock::from_time_t(time).time_since_epoch();
        auto chronoMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint).count();

        // Because std::tm only support seconds we must add the given milliseconds.
        auto newDate = FromUnixEpochMilliseconds(chronoMilliseconds + millisecond, kind);

        // Assign members from newDate to this and we're done.
        *this = newDate;
    }

    DateTime DateTime::ToLocalTime() const
    {
        if (m_Kind == DateTimeKind::Local)
            return *this;

        return FromUnixEpochMilliseconds(m_UnixEpochMilliseconds, DateTimeKind::Local);
    }

    DateTime DateTime::ToUniversalTime() const
    {
        if (m_Kind == DateTimeKind::Utc)
            return *this;

        return FromUnixEpochMilliseconds(m_UnixEpochMilliseconds, DateTimeKind::Utc);
    }

    DateTime DateTime::Add(const TimeSpan &timespan) const
    {
        return AddMilliseconds(timespan.TotalMilliseconds());
    }

    TimeSpan DateTime::Subtract(const DateTime &datetime) const
    {
        if (m_Kind == DateTimeKind::Utc)
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
        if (m_Kind != DateTimeKind::Utc)
            return ToUniversalTime().AddMilliseconds(milliseconds).ToLocalTime();

        return FromUnixEpochMilliseconds(m_UnixEpochMilliseconds + std::llround(milliseconds), m_Kind);
    }

    uint32_t DateTime::Year() const
    {
        return m_Year;
    }

    uint32_t DateTime::Month() const
    {
        return m_Month;
    }

    uint32_t DateTime::Day() const
    {
        return m_Day;
    }

    uint32_t DateTime::Hour() const
    {
        return m_Hour;
    }

    uint32_t DateTime::Minute() const
    {
        return m_Minute;
    }

    uint32_t DateTime::Second() const
    {
        return m_Second;
    }

    uint32_t DateTime::Millisecond() const
    {
        return m_Millisecond;
    }

    uint32_t DateTime::DayOfYear() const
    {
        return m_DayOfYear;
    }

    DayOfWeekEnum DateTime::DayOfWeek() const
    {
        return m_DayOfWeek;
    }

    DateTimeKind DateTime::Kind() const
    {
        return m_Kind;
    }

    bool DateTime::IsDaylightSavingTime() const
    {
        return m_IsDaylightSavingTime;
    }

    DateTime DateTime::UnixEpoch()
    {
        static DateTime unixEpoch = DateTime::FromUnixEpochMilliseconds(0, DateTimeKind::Utc);
        return unixEpoch;
    }

    DateTime DateTime::Parse(const String &input)
    {
        if(input.IsNull())
            throw ArgumentNullException("input");

        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
        char zulu;
        CharBuffer cb = Encoding::ConvertTo<CharBuffer>(input);
        int ret = std::sscanf(cb, "%d-%d-%dT%d:%d:%d%c", &year, &month, &day, &hour, &minute, &second, &zulu);
        if (ret != 7)
            throw FormatException("Input does not contain a valid string representation of a date and time.");

        return DateTime(year, month, day, hour, minute, second, zulu == 'Z');
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

    bool DateTime::operator==(const DateTime &rhs) const noexcept
    {
        return m_UnixEpochMilliseconds == rhs.m_UnixEpochMilliseconds;
    }

    bool DateTime::operator!=(const DateTime &rhs) const noexcept
    {
        return m_UnixEpochMilliseconds != rhs.m_UnixEpochMilliseconds;
    }

    bool DateTime::operator>(const DateTime &rhs) const noexcept
    {
        return m_UnixEpochMilliseconds > rhs.m_UnixEpochMilliseconds;
    }

    bool DateTime::operator>=(const DateTime &rhs) const noexcept
    {
        return m_UnixEpochMilliseconds >= rhs.m_UnixEpochMilliseconds;
    }

    bool DateTime::operator<(const DateTime &rhs) const noexcept
    {
        return m_UnixEpochMilliseconds < rhs.m_UnixEpochMilliseconds;
    }

    bool DateTime::operator<=(const DateTime &rhs) const noexcept
    {
        return m_UnixEpochMilliseconds <= rhs.m_UnixEpochMilliseconds;
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

    TimeSpan::TimeSpan(int32_t hours, int32_t minutes, int32_t seconds)
        : TimeSpan(0, hours, minutes, seconds, 0)
    {
    }

    TimeSpan::TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds)
        : TimeSpan(days, hours, minutes, seconds, 0)
    {
    }

    TimeSpan::TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds, int32_t milliseconds)
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

    int32_t TimeSpan::Days() const
    {
        return m_Days;
    }

    double TimeSpan::TotalDays() const
    {
        return m_TotalDays;
    }

    int32_t TimeSpan::Hours() const
    {
        return m_Hours;
    }

    double TimeSpan::TotalHours() const
    {
        return m_TotalHours;
    }

    int32_t TimeSpan::Minutes() const
    {
        return m_Minutes;
    }

    double TimeSpan::TotalMinutes() const
    {
        return m_TotalMinutes;
    }

    int32_t TimeSpan::Seconds() const
    {
        return m_Seconds;
    }

    double TimeSpan::TotalSeconds() const
    {
        return m_TotalSeconds;
    }

    int32_t TimeSpan::Milliseconds() const
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