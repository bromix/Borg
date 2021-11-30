#pragma once
#include "Base.h"

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
         * @brief Converts the specified Unix Epoch time to an equivalent local or Coordinated Universal Time (UTC) time.
         *
         * @param secondsSinceEpoch
         * @param kind
         * @return DateTime
         */
        static DateTime FromUnixEpochSeconds(uint64 secondsSinceEpoch, DateTimeKindEnum kind = DateTimeKindEnum::Utc);

        /**
         * @brief Converts the specified Unix Epoch time to an equivalent local or Coordinated Universal Time (UTC) time.
         *
         * @param millisecondsSinceEpoch
         * @param kind
         * @return DateTime
         */
        static DateTime FromUnixEpochMilliseconds(uint64 millisecondsSinceEpoch, DateTimeKindEnum kind = DateTimeKindEnum::Utc);

        /**
         * @brief Returns the number of days in the specified month and year.
         *
         * @param year
         * @param month
         * @return uint32
         */
        static uint32 DaysInMonth(uint32 year, uint32 month);

        /**
         * @brief Returns an indication whether the specified year is a leap year.
         *
         * @param year
         * @return true
         * @return false
         */
        static bool IsLeapYear(uint32 year);

        /**
         * @brief Initializes a new instance of the DateTime structure to the specified year, month, day and Coordinated Universal Time (UTC) or local time.
         *
         * @param year
         * @param month
         * @param day
         * @param kind
         */
        DateTime(uint32 year, uint32 month, uint32 day, DateTimeKindEnum kind = DateTimeKindEnum::Local);

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
        DateTime(uint32 year, uint32 month, uint32 day, uint32 hour, uint32 minute, uint32 second, DateTimeKindEnum kind = DateTimeKindEnum::Local);

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
        DateTime(uint32 year, uint32 month, uint32 day, uint32 hour, uint32 minute, uint32 second, uint32 millisecond, DateTimeKindEnum kind = DateTimeKindEnum::Local);

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
         * @return int32
         */
        uint32 Year() const;

        /**
         * @brief Gets the month component of the date represented by this instance.
         *
         * @return int32
         */
        uint32 Month() const;

        /**
         * @brief Gets the day of the month represented by this instance.
         *
         * @return int32
         */
        uint32 Day() const;

        /**
         * @brief Gets the hour component of the date represented by this instance.
         *
         * @return int32
         */
        uint32 Hour() const;

        /**
         * @brief Gets the minute component of the date represented by this instance.
         *
         * @return int32
         */
        uint32 Minute() const;

        /**
         * @brief Gets the seconds component of the date represented by this instance.
         *
         * @return int32
         */
        uint32 Second() const;

        /**
         * @brief Gets the milliseconds component of the date represented by this instance.
         *
         * @return int32
         */
        uint32 Millisecond() const;

        /**
         * @brief Gets the day of the year represented by this instance.
         *
         * @return int32
         */
        uint32 DayOfYear() const;

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

        DateTime operator+(const TimeSpan &timespan);
        TimeSpan operator-(const DateTime &rhs);

    private:
        DateTime();
        uint32 m_Year = 0;
        uint32 m_Month = 0;
        uint32 m_Day = 0;
        uint32 m_Hour = 0;
        uint32 m_Minute = 0;
        uint32 m_Second = 0;
        uint32 m_Millisecond;
        uint32 m_DayOfYear = 0;
        DayOfWeekEnum m_DayOfWeek = DayOfWeekEnum::Sunday;
        uint64 m_UnixEpochMilliseconds = 0;
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
        TimeSpan(int32 hours, int32 minutes, int32 seconds);

        /**
         * @brief Initializes a new instance of the TimeSpan structure to a specified number of days, hours, minutes, and seconds.
         *
         * @param days
         * @param hours
         * @param minutes
         * @param seconds
         */
        TimeSpan(int32 days, int32 hours, int32 minutes, int32 seconds);

        /**
         * @brief Initializes a new instance of the TimeSpan structure to a specified number of days, hours, minutes, seconds, and milliseconds.
         *
         * @param days
         * @param hours
         * @param minutes
         * @param seconds
         * @param milliseconds
         */
        TimeSpan(int32 days, int32 hours, int32 minutes, int32 seconds, int32 milliseconds);

        /**
         * @brief Gets the days component of the time interval represented by the current TimeSpan structure.
         *
         * @return int32
         */
        int32 Days() const;

        /**
         * @brief Gets the value of the current TimeSpan structure expressed in whole and fractional days.
         *
         * @return double
         */
        double TotalDays() const;

        /**
         * @brief Gets the hours component of the time interval represented by the current TimeSpan structure.
         *
         * @return int32
         */
        int32 Hours() const;

        /**
         * @brief Gets the value of the current TimeSpan structure expressed in whole and fractional hours.
         *
         * @return double
         */
        double TotalHours() const;

        /**
         * @brief Gets the minutes component of the time interval represented by the current TimeSpan structure.
         *
         * @return int32
         */
        int32 Minutes() const;

        /**
         * @brief Gets the value of the current TimeSpan structure expressed in whole and fractional minutes.
         *
         * @return double
         */
        double TotalMinutes() const;

        /**
         * @brief Gets the seconds component of the time interval represented by the current TimeSpan structure.
         *
         * @return int32
         */
        int32 Seconds() const;

        /**
         * @brief Gets the value of the current TimeSpan structure expressed in whole and fractional seconds.
         *
         * @return double
         */
        double TotalSeconds() const;

        /**
         * @brief Gets the milliseconds component of the time interval represented by the current TimeSpan structure.
         *
         * @return int32
         */
        int32 Milliseconds() const;

        /**
         * @brief Gets the value of the current TimeSpan structure expressed in whole and fractional milliseconds.
         *
         * @return double
         */
        double TotalMilliseconds() const;

    private:
        int32 m_Days;
        double m_TotalDays;

        int32 m_Hours;
        double m_TotalHours;

        int32 m_Minutes;
        double m_TotalMinutes;

        int32 m_Seconds;
        double m_TotalSeconds;

        int32 m_Milliseconds;
        double m_TotalMilliseconds;
    };
}