#include "mail_sender.hpp"

#include "domain/mail.hpp"

#include "file_data/file.hpp"
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

    auto table = file::File::getTable(msg.get_part_by_name("data").body,
                                      file::FileType::String);

    dom::Mail mail(login, password);
    for (auto& row : table)
    {
        std::string copy = text;
        for (auto& el : row)
        {
            int num;
            while ((num = copy.find(el.first)) != std::string::npos)
            {
                copy.replace(num, el.second.size(), el.second);
            }
        }
        mail.send(row["$mail$"], theme, copy);
    }

    return "mail";
}
