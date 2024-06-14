#include "date_time.hpp"

//--------------------------------------------------------------------------------

void
core::DateTime::set(uint64_t aValue, DateTime::Period aType)
{
    const uint8_t typeVal = uint8_t(aType);
    value &= ~(255ULL >> typeVal << 8 | 255ULL << typeVal);
    value |= aValue << typeVal;
}

//--------------------------------------------------------------------------------

bool
core::DateTime::operator<(const DateTime& aOther) const noexcept
{
    return value < aOther.value;
}

core::DateTime
core::DateTime::operator-(const DateTime& aOther) const noexcept
{
    DateTime result;
    result.value = value - aOther.value;
    return result;
}

//--------------------------------------------------------------------------------

str::String
core::DateTime::getTime() const noexcept
{
    str::String result(10);
    std::sprintf((char*)result.data(), "%02d:%02d:%02d", dateTime.time.hours,
                 dateTime.time.minutes, dateTime.time.seconds);
    return result;
}

str::String
core::DateTime::getDate() const noexcept
{
    str::String result(12);
    std::sprintf((char*)result.data(), "%04d-%02d-%02d", dateTime.date.year,
                 dateTime.date.month, dateTime.date.day);
    return result;
}

str::String
core::DateTime::getAll(char aDelimiter) const noexcept
{
    str::String result;
    result.reserve(22);

    result += getDate();
    result.push_back(aDelimiter);
    result += getTime();

    return result;
}
