#ifndef DATE_AND_TIME_HPP
#define DATE_AND_TIME_HPP

#include <boost/date_time/gregorian/gregorian.hpp>

#include <string>

namespace dom
{
class DateAndTime
{
public:
    static std::string getCurentTime() noexcept;
    static boost::gregorian::date getDate(const std::string& aDate) noexcept;
};
} // namespace dom

//--------------------------------------------------------------------------------

#endif // !DATE_AND_TIME_HPP
