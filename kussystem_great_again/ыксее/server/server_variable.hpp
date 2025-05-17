#pragma once

//--------------------------------------------------------------------------------

#include "core/holy_trinity.hpp"

#include "string/kus_string.hpp"

//--------------------------------------------------------------------------------

namespace serv
{
enum ServerVariables
{
    TOKEN_STATUS_VAR,
    STATUS_VAR_END
};

enum TokenStatus
{
    NUN,
    TURN_OFF,
    TURN_ON,
    MEMORY,
    PRINT
};

class ServerVariableHandlers
{
public:
    static int getTokenStatus(const char* aVar) noexcept;

private:
    HOLY_TRINITY_NO_OBJECT(ServerVariableHandlers);
};

} // namespace serv

//--------------------------------------------------------------------------------
