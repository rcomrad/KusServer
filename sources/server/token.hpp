#pragma once

//--------------------------------------------------------------------------------

#include <optional>
#include <string>

#include "core/variable/variable.hpp"

#include "utility/common/holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace serv
{

class Token
{
public:
    enum Status
    {
        NUN,
        TURN_OFF,
        TURN_ON,
        MEMORY,
        PRINT
    };

    VARIABLE_PARSER(getTokenStatus);
};

} // namespace serv

//--------------------------------------------------------------------------------
