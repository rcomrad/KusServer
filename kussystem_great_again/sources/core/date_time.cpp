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

// core::DateTime::TimeType
// core::DateTime::getTime() const noexcept
// {
//     kstd::CharBuffer result;
//     std::sprintf((char*)result.data(), "%02d:%02d:%02d", dateTime.time.hours,
//                  dateTime.time.minutes, dateTime.time.seconds);
//     return result;
// }

// core::DateTime::DateType
// core::DateTime::getDate() const noexcept
// {
//     kstd::CharBuffer result;
//     std::sprintf((char*)result.data(), "%04d-%02d-%02d", dateTime.date.year,
//                  dateTime.date.month, dateTime.date.day);
//     return result;
// }

// core::DateTime::DateTimeType
// core::DateTime::getAll(char aDelimiter) const noexcept
// {
//     kstd::CharBuffer result;
//     result += getDate();
//     result.push_back(aDelimiter);
//     result += getTime();

//     return result;
// }
