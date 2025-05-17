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
    static str::String getCurentTime() noexcept;
    static str::String getCurentTimeSafe() noexcept;

    static boost::gregorian::date getDate(const char* aDate) noexcept;
    static boost::posix_time::ptime getTime(const char* aTime) noexcept;

    static str::String getDateStr(const boost::gregorian::date& aDate) noexcept;
    static str::String toStr(const boost::posix_time::ptime& aTime) noexcept;
    static bool curentTimeAssert(
        const char* aTime,
        const boost::posix_time::time_duration& aDuration) noexcept;
    static bool curentTimeAssert(
        const boost::posix_time::ptime& aTime,
        const boost::posix_time::time_duration& aDuration) noexcept;
    static bool isPassed(const char* aTime) noexcept;
};
} // namespace dom

//--------------------------------------------------------------------------------

#endif // !DATE_AND_TIME_HPP
