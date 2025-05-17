#pragma once

#include "date_time.hpp"
#include "holy_trinity.hpp"

namespace core
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
} // namespace core

//--------------------------------------------------------------------------------
