#include "mail_sender.hpp"

#include "domain/mail.hpp"

#include "file_data/parser.hpp"
#include "post/post_handler.hpp"

// TODO: crow::multipart::message
std::string
mult::MailSender::process(const crow::request& aReq) noexcept
{
    crow::multipart::message msg(aReq);

    std::string login    = msg.get_part_by_name("login").body;
    std::string password = msg.get_part_by_name("password").body;

    std::string theme = msg.get_part_by_name("theme").body;
    std::string text  = msg.get_part_by_name("text").body;

    auto address =
        file::Parser::slice(msg.get_part_by_name("address").body, ";");

        

    dom::Mail mail(login, password);
    for (auto& a : address)
    {
        mail.send(a, theme, text);
    }

    return "mail";
}
