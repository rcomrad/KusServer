#ifndef TIME_HANDLER_HPP
#define TIME_HANDLER_HPP

#include "date_time.hpp"

namespace dom
{
class TimeHandler
{
public:
    // static boost::posix_time::ptime getRawCurentTime() noexcept;
    // static std::string getCurentTime() noexcept;
    // static std::string getCurentTimeSafe() noexcept;

    // static boost::gregorian::date getDate(const std::string& aDate) noexcept;
    // static boost::posix_time::ptime getTime(const std::string& aTime)
    // noexcept;

    // static std::string getDateStr(const boost::gregorian::date& aDate)
    // noexcept; static std::string toStr(const boost::posix_time::ptime& aTime)
    // noexcept; static bool curentTimeAssert(
    //     const std::string& aTime,
    //     const boost::posix_time::time_duration& aDuration) noexcept;
    // static bool curentTimeAssert(
    //     const boost::posix_time::ptime& aTime,
    //     const boost::posix_time::time_duration& aDuration) noexcept;
    // static bool isPassed(const std::string& aTime) noexcept;

    static DateTime getCurentTime() noexcept;
    // static DateTime create(const boost::gregorian::date& aDate) noexcept;

    static bool dateTimeHasPassed(const DateTime& aTimeMoment) noexcept;
    static bool durationHasPassed(const DateTime& aTimeFrom,
                                  const DateTime& aDuration) noexcept;
};
} // namespace dom

//--------------------------------------------------------------------------------

#endif // !TIME_HANDLER_HPP
