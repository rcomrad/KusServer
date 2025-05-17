#include "command_handler.hpp"

#include "domain/date_and_time.hpp"
#include "domain/url_wrapper.hpp"

#include "core/core.hpp"

#include "server/request_unpacker.hpp"
#include "server/token_handler.hpp"

#include "database/connection_manager.hpp"

#include "file_data/file.hpp"
#include "file_data/parser.hpp"
#include "file_data/path.hpp"
#include "module/module_handler.hpp"
#include "post/user_handler.hpp"

#include "dump_manager.hpp"

str::String
mult::CommandHandler::process(const crow::request& aReq) noexcept
{
    crow::multipart::message msg(aReq);

    auto command = serv::RequestUnpacker::getPart(msg, "command");
    auto value   = serv::RequestUnpacker::getPart(msg, "value");

    str::String result;
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

str::String
mult::CommandHandler::process(const char* aCommand,
                              const char* aArgument) noexcept
{
    str::String res = "ERROR\nInvalid command!\n>:(\n";
    if (mod::ModuleHandler::hasCommand(aCommand))
    {
        res = mod::ModuleHandler::processCommand(aCommand, aArgument);
    }
    return res;
}

// str::String
// registration(str::String login,str::String password ,str::String email,
//                                 bool aNeedConfirmation) noexcept
// {
//     str::String resp = "400";

//     auto connection = data::ConnectionManager::getUserConnection();
//     str::String loginCond = "login = " + data::safeWrap(login);
//     data::User user  = connection.val.getData<data::User>(loginCond);

//     if (user.email != "NULL")
//     {
//         resp = "Username already in use!";
//     }
//     else
//     {
//         user.password = password;
//         user.password = email;
//         user.lastLogin = dom::DateAndTime::getCurentTimeSafe();
//         connection.val.write(newUser);
//         resp = "Successful! Check your email.":
//     }

//     return resp;
// }

// str::String
// mult::CommandHandler::info(const crow::request& aReq) noexcept
// {
//     crow::multipart::message msg(aReq);

//     data::User user;
//     user.login      = serv::RequestUnpacker::getPart(msg, "login");
//     user.password   = serv::RequestUnpacker::getPart(msg, "password");
//     user.email      = serv::RequestUnpacker::getPart(msg, "email");

//     // auto login = serv::RequestUnpacker::getPart(msg, "login");
//     // auto password   = serv::RequestUnpacker::getPart(msg, "password");
//     // auto password   = serv::RequestUnpacker::getPart(msg, "email");

//     // str::String result;
//     // if (!command.has_value())
//     // {
//     //     result = "Error: No command specified!";
//     // }
//     // else
//     // {

//     // }

//     return post::UserHandler::registration2(user, );
// }
