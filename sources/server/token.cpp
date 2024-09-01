#include "token.hpp"

#include "core/command/registry.hpp"

void
serv::Token::tokenCommandHandler(core::CommandExtend& a_command) noexcept
{
    CMD_ASSERT(noVars().argCount(1));

    std::string subcommand = "var_set token_status=";
    subcommand += *a_command.arguments.begin();
    core::CommandExtend sub_command(subcommand, nullptr, nullptr);
    core::CommandHandler::processCommand(sub_command);
    a_command.m_result_buffer = std::move(sub_command.m_result_buffer);

    //     if (a_value == "turn_off")
    //     {
    //         result = int(Token::Status::TURN_OFF);
    //         // COMMAND_RETURN_MSG(a_command, "Set token variable to
    //         'turn_off'");
    //     }
    //     else if (a_value == "turn_on")
    //     {
    //         result = int(Token::Status::TURN_ON);
    //         // COMMAND_RETURN_MSG(a_command, "Set token variable to
    //         'turn_on'");
    //     }
    //     else if (a_value == "memory")
    //     {
    //         result = int(Token::Status::MEMORY);
    //         // COMMAND_RETURN_MSG(a_command, "Set token variable to
    //         'memory'");
    //     }
    //     else if (a_value == "print")
    //     {
    //         result = int(Token::Status::PRINT);
    //         // COMMAND_RETURN_MSG(a_command, "Set token variable to
    //         'print'");
    //     }
    //     else
    //     {
    //         // COMMAND_RETURN_ERROR(a_command, "Can't parse token variable
    //         '%s'",
    //         // a_value);
    //     }
}
