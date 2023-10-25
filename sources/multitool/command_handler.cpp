#include "command_handler.hpp"

#include "domain/url_wrapper.hpp"

#include "database/connection_manager.hpp"

#include "core/core.hpp"
#include "file_data/file.hpp"
#include "file_data/parser.hpp"
#include "file_data/path.hpp"
#include "module/module_handler.hpp"
#include "server/request_unpacker.hpp"
#include "server/token_handler.hpp"

#include "dump_manager.hpp"

std::string
mult::CommandHandler::process(const crow::request& aReq) noexcept
{
    crow::multipart::message msg(aReq);

    auto command = serv::RequestUnpacker::getPart(msg, "command");
    auto value   = serv::RequestUnpacker::getPart(msg, "value");

    std::string result;
    if (!command.has_value())
    {
        result = "Error: No command specified!";
    }
    else
    {
        result =
            process(command.value(), value.has_value() ? value.value() : "");
    }

    return result;
}

std::string
mult::CommandHandler::process(const std::string& aCommand,
                              const std::string& aArgument) noexcept
{
    std::string res = "ERROR\nInvalid command!\n>:(\n";
    if (mod::ModuleHandler::hasCommand(aCommand))
    {
        res = mod::ModuleHandler::processCommand(aCommand, aArgument);
    }
    return res;
}
