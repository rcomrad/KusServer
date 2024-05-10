#include "server_variable.hpp"

#include "core/logging.hpp"

int
serv::ServerVariableHandlers::getTokenStatus(const str::string& aVar) noexcept
{
    TokenStatus result = TokenStatus::NUN;
    // TODO: map or constexpr
    // TODO: merge string name and enum defenition
    if (aVar == "turn_off")
    {
        result = TokenStatus::TURN_OFF;
        LOG_INFO("Set token variable to 'turn_off'");
    }
    else if (aVar == "turn_on")
    {
        result = TokenStatus::TURN_ON;
        LOG_INFO("Set token variable to 'turn_on'");
    }
    else if (aVar == "memory")
    {
        result = TokenStatus::MEMORY;
        LOG_INFO("Set token variable to 'memory'");
    }
    else if (aVar == "memory")
    {
        result = TokenStatus::PRINT;
        LOG_INFO("Set token variable to 'print'");
    }
    else
    {
        LOG_ERROR("Can't parse token variable", aVar);
    }
    return int(result);
}
