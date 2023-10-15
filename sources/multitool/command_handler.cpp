#include "command_handler.hpp"

#include "domain/url_wrapper.hpp"

#include "database/connection_manager.hpp"

#include "core/core.hpp"
#include "file_data/file.hpp"
#include "file_data/parser.hpp"
#include "file_data/path.hpp"
#include "server/request_unpacker.hpp"
#include "server/token_handler.hpp"

#include "dump_manager.hpp"

std::unordered_map<std::string,
                   std::function<std::string(const std::string& aValue)>>
    mult::CommandHandler::mSpecialRoutes = {
        {"restart",        &mult::CommandHandler::restart        },
        {"kill",           [](const std::string& aValue)
         { return applyCommand("kill", "kill"); }},
        {"dump",
         [](const std::string& aValue)
         {
             core::VariableStorage::setVariable("args", aValue, 0ms);
             return applyCommand("dump", "dump");
         }                                                       },
        {"dump_as_string",
         [](const std::string& aValue)
         {
             core::VariableStorage::setVariable("args", aValue, 0ms);
             return applyCommand("dump", "dump_as_string");
         }                                                       },
        {"dump_as_html",   [](const std::string& aValue)
         {
             core::VariableStorage::setVariable("args", aValue, 0ms);
             return applyCommand("dump", "dump_as_html");
         }                               }
};

std::unordered_set<std::string> mult::CommandHandler::mLegaCommands = {
    "token",        "question",       "results",  "dump",
    "dump_as_file", "dump_as_string", "user=comp"};

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
mult::CommandHandler::process(const std::string& aType,
                              const std::string& aValue) noexcept
{
    std::string res = "ERROR\nInvalid command!\n>:(\n";
    auto it1        = mSpecialRoutes.find(aType);
    if (it1 != mSpecialRoutes.end()) res = it1->second(aValue);
    else
    {
        auto it2 = mLegaCommands.find(aType);
        if (it2 != mLegaCommands.end()) res = applyCommand(aType, aValue);
    }
    return res;
}
