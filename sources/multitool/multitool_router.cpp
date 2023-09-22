#include "multitool_router.hpp"

#include "mail_sender.hpp"

std::unordered_map<std::string, decltype(&mult::MultiHandler::process)>
    mult::MultitoolRouter::mMultitoolRouter = {
        {"mail", &mult::MailSender::process},
};

std::string
mult::MultitoolRouter::route(const crow::request& aReq)
{
    crow::multipart::message msg(aReq);
    std::string techName = msg.get_part_by_name("techName").body;
    
    std::string result;
    auto it = mMultitoolRouter.find(techName);
    if (it != mMultitoolRouter.end()) result = it->second(aReq);
    return result;
}
