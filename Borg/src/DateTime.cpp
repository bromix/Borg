#include "Borg/DateTime.h"
#include <chrono>

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
        auto milliseconds = millisecondsSinceEpoch % 1000;
        auto secondsSinceEpoch = millisecondsSinceEpoch / 1000;

        std::tm tm = {};
        gmtime_s(&tm, &secondsSinceEpoch);

        DateTime dt{};
        dt.m_Year = tm.tm_year + 1900;
        dt.m_Month = tm.tm_mon + 1;
        dt.m_Day = tm.tm_mday;
        dt.m_Hour = tm.tm_hour;
        dt.m_Minute = tm.tm_min;
        dt.m_Second = tm.tm_sec;
        dt.m_Millisecond = milliseconds;
        dt.m_UnixEpochMilliseconds = millisecondsSinceEpoch;
        dt.m_Kind = DateTimeKind::Utc;

        return dt;
    }

    DateTime DateTime::Now()
    {
        using namespace std::chrono;
        auto now = system_clock::now().time_since_epoch();
        auto millisecondsSinceEpoch = duration_cast<milliseconds>(now).count();
        auto milliseconds = millisecondsSinceEpoch % 1000;
        auto secondsSinceEpoch = millisecondsSinceEpoch / 1000;

        std::tm tm = {};
        localtime_s(&tm, &secondsSinceEpoch);

        DateTime dt{};
        dt.m_Year = tm.tm_year + 1900;
        dt.m_Month = tm.tm_mon + 1;
        dt.m_Day = tm.tm_mday;
        dt.m_Hour = tm.tm_hour;
        dt.m_Minute = tm.tm_min;
        dt.m_Second = tm.tm_sec;
        dt.m_Millisecond = milliseconds;
        dt.m_UnixEpochMilliseconds = millisecondsSinceEpoch;
        dt.m_Kind = DateTimeKind::Local;

        return dt;
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

    DateTimeKind DateTime::Kind() const
    {
        return m_Kind;
    }
}