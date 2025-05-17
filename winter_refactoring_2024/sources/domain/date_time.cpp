#include "date_time.hpp"

//--------------------------------------------------------------------------------

void
dom::DateTime::set(uint64_t aValue, dom::DateTime::Period aType)
{
    const uint8_t typeVal = uint8_t(aType);
    value &= ~(255ULL >> typeVal << 8 | 255ULL << typeVal);
    value |= aValue << typeVal;
}

//--------------------------------------------------------------------------------

bool
dom::DateTime::operator<(const DateTime& aOther) const noexcept
{
    return value < aOther.value;
}

dom::DateTime
dom::DateTime::operator-(const DateTime& aOther) const noexcept
{
    DateTime result;
    result.value = value - aOther.value;
    return result;
}

//--------------------------------------------------------------------------------

std::string
dom::DateTime::getTimeOnly() const noexcept
{
    std::string result;
    result.reserve(10);

    if (dateTime.time.hours < 10) result.push_back('0');
    result += std::to_string(dateTime.time.hours);
    result.push_back(':');

    if (dateTime.time.minutes < 10) result.push_back('0');
    result += std::to_string(dateTime.time.minutes);
    result.push_back(':');

    if (dateTime.time.seconds < 10) result.push_back('0');
    result += std::to_string(dateTime.time.seconds);

    return result;
}

std::string
dom::DateTime::getDateOnly() const noexcept
{
    std::string result;
    result.reserve(12);

    result += std::to_string(dateTime.date.year);
    result.push_back('-');

    if (dateTime.date.month < 10) result.push_back('0');
    result += std::to_string(dateTime.date.month);
    result.push_back('-');

    if (dateTime.date.day < 10) result.push_back('0');
    result += std::to_string(dateTime.date.day);

    return result;
}

std::string
dom::DateTime::getAllWSpace(char aDelimiter) const noexcept
{
    std::string result;
    result.reserve(22);

    result += getDateOnly();
    result.push_back(aDelimiter);
    result += getTimeOnly();

    return result;
}

std::string
dom::DateTime::getAllNoSpace() const noexcept
{
    return getAllWSpace('_');
}
