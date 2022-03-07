#pragma once
#include "Types.h"
#include "String.h"

namespace Borg
{
    /**
     * @brief Specifies whether a DateTime object represents a local time or a Coordinated Universal Time (UTC).
     */
    enum class DateTimeKindEnum
    {
        /**
         * @brief The time represented is local time.
         */
        Local,

        /**
         * @brief The time represented is UTC.
         */
        Utc
    };

    /**
     * @brief Specifies the day of the week.
     */
    enum class DayOfWeekEnum
    {
        Sunday = 0,
        Monday = 1,
        Tuesday = 2,
        Wednesday = 3,
        Thursday = 4,
        Friday = 5,
        Saturday = 6
    };

    /**
     * @brief Represents an instant in time, typically expressed as a date and time of day.
     */
    class TimeSpan;
    class DateTime
    {
    public:
        /**
         * @brief Gets a DateTime object that is set to the current date and time on this computer, expressed as the Coordinated Universal Time (UTC).
         *
         * @return DateTime
         */
        static DateTime UtcNow();

        /**
         * @brief Gets a DateTime object that is set to the current date and time on this computer, expressed as the local time.
         *
         * @return DateTime
         */
        static DateTime Now();

        /**
         * @brief Converts the specified Unix Epoch (1 January 1970) time to an equivalent local or Coordinated Universal Time (UTC) time.
         *
         * @param secondsSinceEpoch
         * @param kind
         * @return DateTime
         */
        static DateTime FromUnixEpochSeconds(uint64_t secondsSinceEpoch, DateTimeKindEnum kind = DateTimeKindEnum::Utc);

        /**
         * @brief Converts the specified Unix Epoch (1 January 1970) time to an equivalent local or Coordinated Universal Time (UTC) time.
         *
         * @param millisecondsSinceEpoch
         * @param kind
         * @return DateTime
         */
        static DateTime FromUnixEpochMilliseconds(uint64_t millisecondsSinceEpoch, DateTimeKindEnum kind = DateTimeKindEnum::Utc);

        /**
         * @brief Converts the specified NetworkTime (1 January 1900) to an equivalent local or Coordinated Universal Time (UTC) time.
         *
         * @param secondsSinceEpoch
         * @param kind
         * @return DateTime
         */
        static DateTime FromNetworkTimeSeconds(uint64_t secondsSinceEpoch, DateTimeKindEnum kind = DateTimeKindEnum::Utc);

        /**
         * @brief Converts the specified NetworkTime (1 January 1900) to an equivalent local or Coordinated Universal Time (UTC) time.
         *
         * @param millisecondsSinceEpoch
         * @param kind
         * @return DateTime
         */
        static DateTime FromNetworkTimeMilliseconds(uint64_t millisecondsSinceEpoch, DateTimeKindEnum kind = DateTimeKindEnum::Utc);

        uint64_t ToNetworkTimeSeconds() const;
        uint64_t ToNetworkTimeMilliseconds() const;

        /**
         * @brief Returns the number of days in the specified month and year.
         *
         * @param year
         * @param month
         * @return uint32_t
         */
        static uint32_t DaysInMonth(uint32_t year, uint32_t month);

        /**
         * @brief Returns an indication whether the specified year is a leap year.
         *
         * @param year
         * @return true
         * @return false
         */
        static bool IsLeapYear(uint32_t year);

        /**
         * @brief Initializes a new instance of the DateTime structure to the specified year, month, day and Coordinated Universal Time (UTC) or local time.
         *
         * @param year
         * @param month
         * @param day
         * @param kind
         */
        DateTime(uint32_t year, uint32_t month, uint32_t day, DateTimeKindEnum kind = DateTimeKindEnum::Local);

        /**
         * @brief Initializes a new instance of the DateTime structure to the specified year, month, day, hour, minute, second and Coordinated Universal Time (UTC) or local time.
         *
         * @param year
         * @param month
         * @param day
         * @param hour
         * @param minute
         * @param second
         * @param kind
         */
        DateTime(uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second, DateTimeKindEnum kind = DateTimeKindEnum::Local);

        /**
         * @brief Initializes a new instance of the DateTime structure to the specified year, month, day, hour, minute, second, millisecond, and Coordinated Universal Time (UTC) or local time.
         *
         * @param year
         * @param month
         * @param day
         * @param hour
         * @param minute
         * @param second
         * @param millisecond
         * @param kind
         */
        DateTime(uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minute, uint32_t second, uint32_t millisecond, DateTimeKindEnum kind = DateTimeKindEnum::Local);

        /**
         * @brief Converts the value of the current DateTime object to local time.
         *
         * @return DateTime
         */
        DateTime ToLocalTime() const;

        /**
         * @brief Converts the value of the current DateTime object to Coordinated Universal Time (UTC).
         *
         * @return DateTime
         */
        DateTime ToUniversalTime() const;

        /**
         * @brief Returns a new DateTime that adds the value of the specified TimeSpan to the value of this instance.
         *
         * @param timespan
         * @return DateTime
         */
        DateTime Add(const TimeSpan &timespan) const;

        /**
         * @brief Returns a new TimeSpan that subtracts the specified date and time from the value of this instance.
         *
         * @param datetime
         * @return TimeSpan
         */
        TimeSpan Subtract(const DateTime &datetime) const;

        /**
         * @brief Returns a new DateTime that subtracts the specified duration from the value of this instance.
         *
         * @param timespan
         * @return DateTime
         */
        DateTime Subtract(const TimeSpan &timespan) const;

        // TODO: DateTime Add(TimeSpan timspan)
        // TODO: DateTime AddYears(double years)
        // TODO: DateTime AddMonth(double month)

        /**
         * @brief Returns a new DateTime that adds the specified number of days to the value of this instance.
         *
         * @param days
         * @return DateTime
         */
        DateTime AddDays(double days) const;

        /**
         * @brief Returns a new DateTime that adds the specified number of hours to the value of this instance.
         *
         * @param hours
         * @return DateTime
         */
        DateTime AddHours(double hours) const;

        /**
         * @brief Returns a new DateTime that adds the specified number of minutes to the value of this instance.
         *
         * @param minutes
         * @return DateTime
         */
        DateTime AddMinutes(double minutes) const;

        /**
         * @brief Returns a new DateTime that adds the specified number of seconds to the value of this instance.
         *
         * @param seconds
         * @return DateTime
         */
        DateTime AddSeconds(double seconds) const;

        /**
         * @brief Returns a new DateTime that adds the specified number of milliseconds to the value of this instance.
         *
         * @param milliseconds
         * @return DateTime
         */
        DateTime AddMilliseconds(double milliseconds) const;

        /**
         * @brief Gets the year component of the date represented by this instance.
         *
         * @return int32_t
         */
        uint32_t Year() const;

        /**
         * @brief Gets the month component of the date represented by this instance.
         *
         * @return int32_t
         */
        uint32_t Month() const;

        /**
         * @brief Gets the day of the month represented by this instance.
         *
         * @return int32_t
         */
        uint32_t Day() const;

        /**
         * @brief Gets the hour component of the date represented by this instance.
         *
         * @return int32_t
         */
        uint32_t Hour() const;

        /**
         * @brief Gets the minute component of the date represented by this instance.
         *
         * @return int32_t
         */
        uint32_t Minute() const;

        /**
         * @brief Gets the seconds component of the date represented by this instance.
         *
         * @return int32_t
         */
        uint32_t Second() const;

        /**
         * @brief Gets the milliseconds component of the date represented by this instance.
         *
         * @return int32_t
         */
        uint32_t Millisecond() const;

        /**
         * @brief Gets the day of the year represented by this instance.
         *
         * @return int32_t
         */
        uint32_t DayOfYear() const;

        /**
         * @brief Gets the day of the week represented by this instance.
         *
         * @return DayOfWeekType
         */
        DayOfWeekEnum DayOfWeek() const;

        /**
         * @brief Gets a value that indicates whether the time represented by this instance is based on local time or Coordinated Universal Time (UTC).
         *
         * @return DateTimeKindEnum
         */
        DateTimeKindEnum Kind() const;

        /**
         * @brief Indicates whether this instance of DateTime is within the daylight saving time range for the current time zone.
         *
         * @return true
         * @return false
         */
        bool IsDaylightSavingTime() const;

        /**
         * @brief The value of this constant is equivalent to 00:00:00.0000000 UTC, January 1, 1970, in the Gregorian calendar. UnixEpoch defines the point in time when Unix time is equal to 0.
         *
         * @return DateTime
         */
        static DateTime UnixEpoch();

        static DateTime Parse(const String &input);

        /**
         * @brief Adds a specified time interval to a specified date and time, yielding a new date and time.
         *
         * @param timespan
         * @return DateTime
         */
        DateTime operator+(const TimeSpan &timespan);

        /**
         * @brief Subtracts a specified date and time from another specified date and time and returns a time interval.
         *
         * @param rhs
         * @return TimeSpan
         */
        TimeSpan operator-(const DateTime &rhs);

        /**
         * @brief Subtracts a specified time interval from a specified date and time and returns a new date and time.
         *
         * @param timespan
         * @return DateTime
         */
        DateTime operator-(const TimeSpan &timespan);

        bool operator==(const DateTime &rhs) const noexcept;
        bool operator!=(const DateTime &rhs) const noexcept;
        bool operator>(const DateTime &rhs) const noexcept;
        bool operator>=(const DateTime &rhs) const noexcept;
        bool operator<(const DateTime &rhs) const noexcept;
        bool operator<=(const DateTime &rhs) const noexcept;

    private:
        DateTime();
        uint32_t m_Year = 0;
        uint32_t m_Month = 0;
        uint32_t m_Day = 0;
        uint32_t m_Hour = 0;
        uint32_t m_Minute = 0;
        uint32_t m_Second = 0;
        uint32_t m_Millisecond;
        uint32_t m_DayOfYear = 0;
        DayOfWeekEnum m_DayOfWeek = DayOfWeekEnum::Sunday;
        uint64_t m_UnixEpochMilliseconds = 0;
        DateTimeKindEnum m_Kind = DateTimeKindEnum::Utc;
        bool m_IsDaylightSavingTime = false;
    };

    class TimeSpan
    {
    public:
        /**
         * @brief Returns a TimeSpan that represents a specified number of days.
         *
         * @param days
         * @return TimeSpan
         */
        static TimeSpan FromDays(double days);

        /**
         * @brief Returns a TimeSpan that represents a specified number of hours.
         *
         * @param hours
         * @return TimeSpan
         */
        static TimeSpan FromHours(double hours);

        /**
         * @brief Returns a TimeSpan that represents a specified number of minutes.
         *
         * @param minutes
         * @return TimeSpan
         */
        static TimeSpan FromMinutes(double minutes);

        /**
         * @brief Returns a TimeSpan that represents a specified number of seconds.
         *
         * @param seconds
         * @return TimeSpan
         */
        static TimeSpan FromSeconds(double seconds);

        /**
         * @brief Returns a TimeSpan that represents a specified number of milliseconds.
         *
         * @param milliseconds
         * @return TimeSpan
         */
        static TimeSpan FromMilliseconds(double milliseconds);

        /**
         * @brief Initializes a new instance of the TimeSpan structure to a specified number of hours, minutes, and seconds.
         *
         * @param hours
         * @param minutes
         * @param seconds
         */
        TimeSpan(int32_t hours, int32_t minutes, int32_t seconds);

        /**
         * @brief Initializes a new instance of the TimeSpan structure to a specified number of days, hours, minutes, and seconds.
         *
         * @param days
         * @param hours
         * @param minutes
         * @param seconds
         */
        TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds);

        /**
         * @brief Initializes a new instance of the TimeSpan structure to a specified number of days, hours, minutes, seconds, and milliseconds.
         *
         * @param days
         * @param hours
         * @param minutes
         * @param seconds
         * @param milliseconds
         */
        TimeSpan(int32_t days, int32_t hours, int32_t minutes, int32_t seconds, int32_t milliseconds);

        /**
         * @brief Returns a new TimeSpan object whose value is the sum of the specified TimeSpan object and this instance.
         *
         * @param timespan
         * @return TimeSpan
         */
        TimeSpan Add(const TimeSpan &timespan) const;

        /**
         * @brief Returns a new TimeSpan object whose value is the difference between the specified TimeSpan object and this instance.
         *
         * @param timespan
         * @return TimeSpan
         */
        TimeSpan Subtract(const TimeSpan &timespan) const;

        /**
         * @brief Gets the days component of the time interval represented by the current TimeSpan structure.
         *
         * @return int32_t
         */
        int32_t Days() const;

        /**
         * @brief Gets the value of the current TimeSpan structure expressed in whole and fractional days.
         *
         * @return double
         */
        double TotalDays() const;

        /**
         * @brief Gets the hours component of the time interval represented by the current TimeSpan structure.
         *
         * @return int32_t
         */
        int32_t Hours() const;

        /**
         * @brief Gets the value of the current TimeSpan structure expressed in whole and fractional hours.
         *
         * @return double
         */
        double TotalHours() const;

        /**
         * @brief Gets the minutes component of the time interval represented by the current TimeSpan structure.
         *
         * @return int32_t
         */
        int32_t Minutes() const;

        /**
         * @brief Gets the value of the current TimeSpan structure expressed in whole and fractional minutes.
         *
         * @return double
         */
        double TotalMinutes() const;

        /**
         * @brief Gets the seconds component of the time interval represented by the current TimeSpan structure.
         *
         * @return int32_t
         */
        int32_t Seconds() const;

        /**
         * @brief Gets the value of the current TimeSpan structure expressed in whole and fractional seconds.
         *
         * @return double
         */
        double TotalSeconds() const;

        /**
         * @brief Gets the milliseconds component of the time interval represented by the current TimeSpan structure.
         *
         * @return int32_t
         */
        int32_t Milliseconds() const;

        /**
         * @brief Gets the value of the current TimeSpan structure expressed in whole and fractional milliseconds.
         *
         * @return double
         */
        double TotalMilliseconds() const;

        /**
         * @brief Adds two specified TimeSpan instances.
         *
         * @param timespan
         * @return TimeSpan
         */
        TimeSpan operator+(const TimeSpan &timespan);

        /**
         * @brief Subtracts a specified TimeSpan from another specified TimeSpan.
         *
         * @param timespan
         * @return TimeSpan
         */
        TimeSpan operator-(const TimeSpan &timespan);

    private:
        int32_t m_Days;
        double m_TotalDays;

        int32_t m_Hours;
        double m_TotalHours;

        int32_t m_Minutes;
        double m_TotalMinutes;

        int32_t m_Seconds;
        double m_TotalSeconds;

        int32_t m_Milliseconds;
        double m_TotalMilliseconds = 0;
    };
}