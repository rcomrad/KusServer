#pragma once

//--------------------------------------------------------------------------------

#include <cstdint>

#include "string/kus_string.hpp"

//--------------------------------------------------------------------------------

namespace util
{

union DateTime
{
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

    str::string getTime() const noexcept;
    str::string getDate() const noexcept;
    str::string getAll(char aDelimiter = '_') const noexcept;
};

} // namespace util

//--------------------------------------------------------------------------------
