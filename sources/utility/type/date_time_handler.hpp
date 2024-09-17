#pragma once

#include "utility/common/holy_trinity.hpp"

#include "date_time.hpp"

namespace util
{
class DateTimeHandler
{
public:
    HOLY_TRINITY_NO_OBJECT(DateTimeHandler);

    static DateTime getCurentTime() noexcept;

    static bool dateTimeHasPassed(const DateTime& aTimeMoment) noexcept;
    static bool durationHasPassed(const DateTime& aTimeFrom,
                                  const DateTime& aDuration) noexcept;
};
} // namespace util

//--------------------------------------------------------------------------------
