#include "multitool_router.hpp"

#include "general_tools/log.hpp"

// #include "core/token_handler.hpp"

#include "domain/variable_storage.hpp"

#include "server/server.hpp"

#include "command_handler.hpp"
#include "dump_manager.hpp"
#include "mail_sender.hpp"

std::unordered_map<std::string, mult::MultitoolRouter::Rote>
    mult::MultitoolRouter::mMultitoolRouter = generateMultitoolRouter();

crow::response
mult::MultitoolRouter::route(const crow::request& aReq)
{
    static const bool& isTokenActive =
        dom::VariableStorage::touchFlag("token:isActive", false);
    // LOG_INFO("-||->GG");
    crow::response result;

    auto& ctx = serv::Server::getContext(aReq);

    crow::multipart::message msg(aReq);
    // TODO: check if no name
    std::string techName = msg.get_part_by_name("techName").body;

    auto it = mMultitoolRouter.find(techName);
    if (it != mMultitoolRouter.end())
    {
        // TODO: use storage flag
        if (!isTokenActive || ctx.mUser->role & it->second.roles)
        {
            crow::json::wvalue json;
            json["html"] = it->second.func(aReq);
            result       = std::move(json);
        }
        else
        {
            LOG_INFO("My role:", ctx.mUser->role,
                     "Needed role:", it->second.roles);
            result      = {"Access denied!"};
            result.code = 403;
        }
    }
    else
    {
        result      = {"No such tool!"};
        result.code = 409;
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
