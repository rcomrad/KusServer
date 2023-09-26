#include "user_handler.hpp"

#include <sstream>

#include "domain/date_and_time.hpp"
#include "domain/mail.hpp"

#include "database/connection_manager.hpp"

#include "core/role.hpp"
#include "core/token_handler.hpp"
#include "file_data/file.hpp"
#include "file_data/parser.hpp"
#include "file_data/path.hpp"
#include "get/get_handler.hpp"

std::mutex post::UserHandler::mRegMut;
std::mutex post::UserHandler::mmConformMut;
std::unordered_map<std::string, int> post::UserHandler::mConformationUrls;

crow::json::wvalue
post::UserHandler::process(post::PostRequest<data::User>& aReq) noexcept
{
    // //TODO: move somevere
    //     int tt;
    //     for (auto& i : request.manyToMany)
    //     {
    //         transmitToMTMHandler(i.first, tt, request.other.count("add"),
    //                              i.second);
    //     }

    auto it = aReq.leftovers.find("role");
    if (it != aReq.leftovers.end())
    {
        std::set<std::string> roles;
        for (auto& i : it->second)
        {
            roles.insert(i.s());
        }

        aReq.data.roleID = core::Role::getInstance().getRoleID(roles);
    }
    aReq.leftovers.erase("role");

    int res;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        fiil(aReq.data);
        res = connection.val.write(aReq.data);
    }

    return {res};
}

crow::json::wvalue
post::UserHandler::rawDataHandler(data::RawData& aData) noexcept
{
    for (size_t i = 0; i < aData.value.size(); ++i)
    {
        if (aData.additionalInfo.size() && aData.additionalInfo[i].size())
        {
            std::set<std::string> roles;
            for (auto& j : aData.additionalInfo[i])
            {
                roles.insert(j);
            }

            // TODO: remove insert
            aData.value[i].insert(
                aData.value[i].begin() + 5,
                data::wrap(core::Role::getInstance().getRoleID(roles)));
        }
    }

    return rawDataInsert<data::User>(aData.value);
}

crow::response
post::UserHandler::autorisation(const crow::request& aReq) noexcept
{
    auto x    = crow::json::load(aReq.body);
    auto resp = crow::response(400);
    if (x)
    {
        // data::DatabaseQuery dbq(data::DatabaseQuery::UserType::USER);
        data::User user = parseRequest<data::User>(x).data;

        std::string cond = "login = \'" + user.login + "\' AND " +
                           "password = \'" + user.password + "\'";
        {
            auto connection = data::ConnectionManager::getUserConnection();
            user            = connection.val.getData<data::User>(cond);
        }

        if (user.id && user.status > 0)
        {
            crow::json::wvalue uJson;
            uJson["user"] = user.getAsJson({"password", "role_id"});

            auto& tokenHandler = core::TokenHandler::getInstance();
            if (tokenHandler.isActive())
                uJson["user"]["token"] = tokenHandler.generate(user);

            auto roles = core::Role::getInstance().getRoles(user.roleID);
            crow::json::wvalue::list roleList;
            for (auto& i : roles)
            {
                roleList.emplace_back(std::move(i));
            }
            uJson["user"]["role"] = std::move(roleList);

            resp = std::move(uJson);
        }
        else
        {
            resp = crow::response(401);
        }
    }
    // resp = crow::response(401);
    return resp;
}

crow::response
post::UserHandler::registration(const crow::request& aReq,
                                bool aNoConfirmation) noexcept
{
    auto body = crow::json::load(aReq.body);
    auto resp = crow::response(400);
    if (body)
    {
        data::User newUser = parseRequest<data::User>(body).data;
        std::string cond   = "login = \'" + newUser.login + "\'";

        mRegMut.lock();
        auto connection        = data::ConnectionManager::getUserConnection();
        data::User existedUser = connection.val.getData<data::User>(cond);

        if (!existedUser.id)
        {
            fiil(newUser);
            newUser.status = -1;

            auto url = send(newUser.email);
            if (setRole(newUser) && !url.empty())
            {
                crow::json::wvalue temp;
                temp["id"] = connection.val.write(newUser);
                resp       = std::move(temp);

                mmConformMut.lock();
                mConformationUrls[url] = newUser.id;
                mmConformMut.unlock();
            }
            else
            {
                resp = crow::response(401);
            }
        }
        else
        {
            resp = crow::response(401);
        }

        mRegMut.unlock();
    }
    // resp = crow::response(401);
    return resp;
}

bool
post::UserHandler::confirm(const std::string& aUrl) noexcept
{
    bool result = false;
    mmConformMut.lock();

    auto it = mConformationUrls.find(aUrl);
    if (it != mConformationUrls.end())
    {
        auto connection = data::ConnectionManager::getUserConnection();
        auto user =
            connection.val.getData<data::User>("id=" + data::wrap(it->second));
        user.status = 1;
        connection.val.write(user);

        mConformationUrls.erase(it);
        result = true;
    }

    mmConformMut.unlock();
    return result;
}

void
post::UserHandler::fiil(data::User& aUser) noexcept
{
    if (aUser.name.empty()) aUser.name = "NUN";
    if (aUser.surname.empty()) aUser.surname = "NUN";

    if (aUser.schoolID == 0) aUser.schoolID = -1;

    if (aUser.email.empty()) aUser.email = "NUN";
    if (aUser.key.empty()) aUser.key = "NUN";

    if (aUser.status == 0) aUser.status = 10;
}

std::unordered_map<std::string, std::set<std::string>>
foo2()
{
    std::unordered_map<std::string, std::set<std::string>> result;
    auto data = file::File::getLines("config", "key_role.conf");
    for (int i = 0; i < data.size(); i += 2)
    {
        auto roles      = file::Parser::slice(data[i + 1], " ");
        result[data[i]] = std::set<std::string>(roles.begin(), roles.end());
    }
    result["NUN"] = {""};
    return result;
}

bool
post::UserHandler::setRole(data::User& aUser) noexcept
{
    bool result       = false;
    static auto roles = foo2();
    auto it           = roles.find(aUser.key);
    if (it != roles.end())
    {
        aUser.roleID = core::Role::getInstance().getRoleID(it->second);
        result       = true;
    }
    return result;
}

std::string
post::UserHandler::send(const std::string& aEmail) noexcept
{
    static auto pass =
        file::File::getWords(file::Path::getPathUnsafe("config", "mail.pass"));
    static dom::Mail mail(pass[0][0], pass[0][1]);

    static auto curSiteUrl = file::File::getWords("config", "url.pass")[0][0];

    std::string url = dom::DateAndTime::getCurentTimeSafe();
    for (int i = 0; i < 10; ++i) url += 'a' + rand() % 26;

    mail.send(aEmail, "Ссылка для подтверждения kussystem",
              "https://" + curSiteUrl + "/api/confirm/" + url);

    return url;
}
