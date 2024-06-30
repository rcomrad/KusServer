#include "token.hpp"

#include "core/logging.hpp"
#include "core/variable_storage.hpp"

int
serv::Token::getTokenStatus(const str::string& aVar) noexcept
{
    int result = core::VariableStorage::CORRUPTED_VALUE;
    // TODO: map or constexpr
    // TODO: merge string name and enum defenition
    if (aVar == "turn_off")
    {
        result = int(Token::Status::TURN_OFF);
        LOG_INFO("Set token variable to 'turn_off'");
    }
    else if (aVar == "turn_on")
    {
        result = int(Token::Status::TURN_ON);
        LOG_INFO("Set token variable to 'turn_on'");
    }
    else if (aVar == "memory")
    {
        result = int(Token::Status::MEMORY);
        LOG_INFO("Set token variable to 'memory'");
    }
    else if (aVar == "print")
    {
        result = int(Token::Status::PRINT);
        LOG_INFO("Set token variable to 'print'");
    }
    else
    {
        LOG_ERROR("Can't parse token variable", aVar);
    }
    return result;
}