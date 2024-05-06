#include "server_variable.hpp"

int
serv::ServerVariableHandlers::getTokenStatus(const str::string& aVar) noexcept
{
    TokenStatus result = TokenStatus::NUN;
    // TODO: map or constexpr
    // TODO: merge string name and enum defenition
    if (aVar == "turn_off")
    {
        result = TokenStatus::TURN_OFF;
    }
    else if (aVar == "turn_on")
    {
        result = TokenStatus::TURN_ON;
    }
    else if (aVar == "memory")
    {
        result = TokenStatus::MEMORY;
    }
    else if (aVar == "memory")
    {
        result = TokenStatus::PRINT;
    }
    return int(result);
}
