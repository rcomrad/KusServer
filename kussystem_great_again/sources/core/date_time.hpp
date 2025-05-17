#pragma once

//--------------------------------------------------------------------------------

#include "kus_standard/char_buffer.hpp"

//--------------------------------------------------------------------------------

namespace core
{

union DateTime
{
    // TODO: too agly
    inline static const char TIME[]        = "Time";
    inline static const char Date[]        = "Date";
    inline static const char DateTimeStr[] = "DateTime";

    using DateTimeType = kstd::CharBuffer<TIME, 22>;
    using DateType     = kstd::CharBuffer<Date, 12>;
    using TimeType     = kstd::CharBuffer<DateTimeStr, 10>;

    enum class Type
    {
        DATE,
        TIME
    };
    enum class Period
    {
        Year    = 0,
        Month   = 16,
        Day     = 24,
        Hours   = 32,
        Minutes = 40,
        Seconds = 48
    };

    struct DateTimeStruct
    {
        struct Date
        {
            uint16_t year;
            uint8_t month;
            uint8_t day;
        } date;
        struct Time
        {
            uint8_t hours;
            uint8_t minutes;
            uint8_t seconds;
            uint8_t filler;
        } time;
    } dateTime;
    uint64_t value = 0;

    void set(uint64_t aValue, Period aType);

    bool operator<(const DateTime& aOther) const noexcept;
    DateTime operator-(const DateTime& aOther) const noexcept;

    // TimeType getTime() const noexcept;
    // DateType getDate() const noexcept;
    // DateTimeType getAll(char aDelimiter = '_') const noexcept;
};

} // namespace core

//--------------------------------------------------------------------------------
