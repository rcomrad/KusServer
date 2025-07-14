#include "date_time.hpp"

//--------------------------------------------------------------------------------

void
util::DateTime::set(uint64_t aValue, DateTime::Period aType)
{
    const uint8_t typeVal = uint8_t(aType);
    value &= ~(255ULL >> typeVal << 8 | 255ULL << typeVal);
    value |= aValue << typeVal;
}

//--------------------------------------------------------------------------------

bool
util::DateTime::operator<(const DateTime& aOther) const noexcept
{
    return value < aOther.value;
}

util::DateTime
util::DateTime::operator-(const DateTime& aOther) const noexcept
{
    DateTime result;
    result.value = value - aOther.value;
    return result;
}

//--------------------------------------------------------------------------------

std::string
util::DateTime::getTime() const noexcept
{
    std::string result(10, '\0');
    std::sprintf((char*)result.data(), "%02d:%02d:%02d", dateTime.time.hours,
                 dateTime.time.minutes, dateTime.time.seconds);
    return result;
}

std::string
util::DateTime::getDate() const noexcept
{
    std::string result(12, '\0');
    std::sprintf((char*)result.data(), "%04d-%02d-%02d", dateTime.date.year,
                 dateTime.date.month, dateTime.date.day);
    return result;
}

std::string
util::DateTime::getAll(char aDelimiter) const noexcept
{
    std::string result;
    result.reserve(22);

    result += getDate();
    result.push_back(aDelimiter);
    result += getTime();

    return result;
}
