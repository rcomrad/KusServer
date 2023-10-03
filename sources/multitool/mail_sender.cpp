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

    auto letter = sliseText(text, *table.begin());

    dom::Mail mail(login, password);
    for (auto& row : table)
    {
        std::string copy;
        for (auto& l : letter)
        {
            copy += l.second + row[l.first];
        }
        mail.send(row["$mail$"], theme, copy);
    }

    return "mail";
}

std::vector<std::pair<std::string, std::string>>
mult::MailSender::sliseText(
    const std::string& aText,
    const std::unordered_map<std::string, std::string>& aKeys) noexcept
{
    std::vector<std::pair<std::string, std::string>> result;

    int last = 0;
    std::unordered_map<std::string, int> count;
    for (int indx = 0; indx < aText.size(); ++indx)
    {
        for (auto& i : aKeys)
        {
            int& num = count[i.first];
            if (aText[indx] == i.first[num])
            {
                ++num;
            }
            else
            {
                num = 0;
            }

            if (num == i.first.size())
            {
                num = 0;
                count.clear();
                result.emplace_back(
                    i.first,
                    aText.substr(last, (indx - last) - i.first.size() + 1));
                last = indx + 1;
            }
        }
    }

    result.emplace_back(""s, aText.substr(last, aText.size()));

    return result;
}
