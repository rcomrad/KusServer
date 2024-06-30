#pragma once

//--------------------------------------------------------------------------------

#include "core/holy_trinity.hpp"

#include "string/kus_string.hpp"

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

    static int getTokenStatus(const str::string& aVar) noexcept;
};

} // namespace serv

//--------------------------------------------------------------------------------
