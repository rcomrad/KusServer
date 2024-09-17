#include "date_time_handler.hpp"

#include <boost/date_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <algorithm>

#include "utility/common/metaprogramming.hpp"

//--------------------------------------------------------------------------------

util::DateTime
util::DateTimeHandler::getCurentTime() noexcept
{
    DateTime result;

    auto curMoment = boost::posix_time::second_clock::local_time();
    auto time      = curMoment.time_of_day();
    auto date      = curMoment.date();

    result.dateTime.date.day   = date.day();
    result.dateTime.date.month = date.month();
    result.dateTime.date.year  = date.year();

    result.dateTime.time.seconds = time.seconds();
    result.dateTime.time.minutes = time.minutes();
    result.dateTime.time.hours   = time.hours();

    return result;
}

//--------------------------------------------------------------------------------

bool
util::DateTimeHandler::dateTimeHasPassed(const DateTime& aTimeMoment) noexcept
{
    static DateTime nullMoment;
    return durationHasPassed(aTimeMoment, nullMoment);
}

bool
util::DateTimeHandler::durationHasPassed(const DateTime& aTimeFrom,
                                         const DateTime& aDuration) noexcept
{
    auto currentTime = getCurentTime();
    return (currentTime - aTimeFrom) < aDuration;
}

//--------------------------------------------------------------------------------
