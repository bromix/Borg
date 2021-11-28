#include "Borg/DateTime.h"
#include <chrono>
#include <cmath>

namespace Borg
{

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

    DateTime DateTime::FromUnixEpochMilliseconds(uint64 millisecondsSinceEpoch, DateTimeKind kind)
    {
        uint32 milliseconds = millisecondsSinceEpoch % 1000;
        int64 secondsSinceEpoch = millisecondsSinceEpoch / 1000;

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
        dt.m_DayOfWeek = static_cast<DayOfWeekType>(tm.tm_wday);
        dt.m_UnixEpochMilliseconds = millisecondsSinceEpoch;
        dt.m_Kind = kind;

        return dt;
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

    DateTime DateTime::AddDays(double days) const
    {
        if (m_Kind != DateTimeKind::Utc)
            return ToUniversalTime().AddDays(days).ToLocalTime();

        uint64 daysInMilliseconds = std::llround(days * 24.0) * 60 * 60 * 1000;
        return FromUnixEpochMilliseconds(m_UnixEpochMilliseconds + daysInMilliseconds, m_Kind);
    }

    int32 DateTime::Year() const
    {
        return m_Year;
    }

    int32 DateTime::Month() const
    {
        return m_Month;
    }

    int32 DateTime::Day() const
    {
        return m_Day;
    }

    int32 DateTime::Hour() const
    {
        return m_Hour;
    }

    int32 DateTime::Minute() const
    {
        return m_Minute;
    }

    int32 DateTime::Second() const
    {
        return m_Second;
    }

    int32 DateTime::Millisecond() const
    {
        return m_Millisecond;
    }

    int32 DateTime::DayOfYear() const
    {
        return m_DayOfYear;
    }

    DayOfWeekType DateTime::DayOfWeek() const
    {
        return m_DayOfWeek;
    }

    DateTimeKind DateTime::Kind() const
    {
        return m_Kind;
    }
}