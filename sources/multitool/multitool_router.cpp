#include "multitool_router.hpp"

#include "core/token_handler.hpp"

#include "command_handler.hpp"
#include "dump_manager.hpp"
#include "mail_sender.hpp"

std::unordered_map<std::string, mult::MultitoolRouter::Rote>
    mult::MultitoolRouter::mMultitoolRouter = generateMultitoolRouter();

std::string
mult::MultitoolRouter::route(const crow::request& aReq)
{
    static bool noAuthorization =
        !core::TokenHandler::getInstance().checkAuthorizationStatus();

    crow::multipart::message msg(aReq);
    // TODO: check if no name
    std::string techName = msg.get_part_by_name("techName").body;

    std::string result;
    auto it = mMultitoolRouter.find(techName);
    if (it != mMultitoolRouter.end())
    {
        auto role = core::TokenHandler::getInstance().getRoleID(aReq);
        if (noAuthorization || role & it->second.roles)
        {
            result = it->second.func(aReq);
        }
        else
        {
            result = "403";
        }
    }
    else
    {
        result = "409";
    }

    return result;
}

std::unordered_map<std::string, mult::MultitoolRouter::Rote>
mult::MultitoolRouter::generateMultitoolRouter() noexcept
{
    std::unordered_map<std::string, Rote> result = {
        {"mail",    {&mult::MailSender::process, 0}    },
        {"dump",    {&mult::DumpManager::process, 0}   },
        {"command", {&mult::CommandHandler::process, 0}},
    };

    auto connection = data::ConnectionManager::getUserConnection();
    auto forms      = connection.val.getDataArray<data::Form>();

    for (auto& r : result)
    {
        for (auto& f : forms)
        {
            if (f.techName == r.first)
            {
                r.second.roles = f.roleID;
                break;
            }
        }
    }

    return result;
}
