#include "date_and_time.hpp"

#include <boost/date_time.hpp>

std::string
dom::DateAndTime::getCurentTime()
{
    boost::posix_time::ptime timeLocal =
        boost::posix_time::second_clock::local_time();

    std::string dateTime;
    dateTime += std::to_string(timeLocal.date().year()) + "-";
    dateTime += std::to_string(timeLocal.date().month()) + "-";
    dateTime += std::to_string(timeLocal.date().day()) + " ";

    dateTime += std::to_string(timeLocal.time_of_day().hours()) + ":";
    dateTime += std::to_string(timeLocal.time_of_day().minutes()) + ":";
    if (timeLocal.time_of_day().seconds() < 10) dateTime += "0";
    dateTime += std::to_string(timeLocal.time_of_day().seconds());

    return dateTime;
}