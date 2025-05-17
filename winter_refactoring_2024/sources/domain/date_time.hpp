#ifndef DATE_TIME_HPP
#define DATE_TIME_HPP

//--------------------------------------------------------------------------------

#include <string>

//--------------------------------------------------------------------------------

namespace dom
{

union DateTime
{
    enum class Type
    {
        Date,
        Time
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

    std::string getTimeOnly() const noexcept;
    std::string getDateOnly() const noexcept;
    std::string getAllWSpace(char aDelimiter = ' ') const noexcept;
    std::string getAllNoSpace() const noexcept;
};

} // namespace dom

//--------------------------------------------------------------------------------

#endif // !DATE_TIME_HPP
