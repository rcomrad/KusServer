#ifndef DATE_AND_TIME_HPP
#define DATE_AND_TIME_HPP

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <string>

namespace dom
{
class DateAndTime
{
public:
    static boost::posix_time::ptime getRawCurentTime() noexcept;
    static std::string getCurentTime() noexcept;
    static std::string getCurentTimeSafe() noexcept;

    static boost::gregorian::date getDate(const std::string& aDate) noexcept;
    static boost::posix_time::ptime getTime(const std::string& aTime) noexcept;

    static std::string getDateStr(const boost::gregorian::date& aDate) noexcept;
    static std::string toStr(const boost::posix_time::ptime& aTime) noexcept;
    static bool curentTimeAssert(
        const std::string& aTime,
        const boost::posix_time::time_duration& aDuration) noexcept;
    static bool curentTimeAssert(
        const boost::posix_time::ptime& aTime,
        const boost::posix_time::time_duration& aDuration) noexcept;
    static bool isPassed(const std::string& aTime) noexcept;
};
} // namespace dom

//--------------------------------------------------------------------------------

#endif // !DATE_AND_TIME_HPP
