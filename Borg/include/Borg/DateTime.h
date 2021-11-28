#pragma once
#include "Base.h"

namespace Borg
{
    /**
     * @brief Represents an instant in time, typically expressed as a date and time of day.
     * 
     */
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
         * @brief Gets the year component of the date represented by this instance.
         * 
         * @return int32 
         */
        int32 Year() const;

        /**
         * @brief Gets the month component of the date represented by this instance.
         * 
         * @return int32 
         */
        int32 Month() const;

        /**
         * @brief Gets the day of the month represented by this instance.
         * 
         * @return int32 
         */
        int32 Day() const;

        /**
         * @brief Gets the hour component of the date represented by this instance.
         * 
         * @return int32 
         */
        int32 Hour() const;

        /**
         * @brief Gets the minute component of the date represented by this instance.
         * 
         * @return int32 
         */
        int32 Minute() const;

        /**
         * @brief Gets the seconds component of the date represented by this instance.
         * 
         * @return int32 
         */
        int32 Second() const;

        /**
         * @brief Gets the milliseconds component of the date represented by this instance.
         * 
         * @return int32 
         */
        int32 Millisecond() const;

    private:
        DateTime();
        uint32 m_Year = 0;
        uint32 m_Month = 0;
        uint32 m_Day = 0;
        uint32 m_Hour = 0;
        uint32 m_Minute = 0;
        uint32 m_Second = 0;
        uint32 m_Millisecond;
        uint64 m_UnixEpochMilliseconds = 0;
    };
}