#include "mail_sender.hpp"

#include <thread>

#include "domain/date_and_time.hpp"
#include "domain/mail.hpp"
#include "domain/url_wrapper.hpp"

#include "file_data/file.hpp"
#include "file_data/parser.hpp"
#include "file_data/path.hpp"
#include "post/post_handler.hpp"

#include "crow_helper.hpp"
// TODO: crow::multipart::message

std::string
mult::MailSender::process(const crow::request& aReq) noexcept
{
    crow::multipart::message msg(aReq);

    Letter letter;
    letter.theme    = CrowHelper::getPart(msg, "theme");
    letter.text     = CrowHelper::getPart(msg, "text");
    letter.login    = CrowHelper::getPart(msg, "login");
    letter.password = CrowHelper::getPart(msg, "password");
    letter.data     = CrowHelper::getPart(msg, "data");

    std::string fileName =
        "mail_report_" + dom::DateAndTime::getCurentTimeSafe() + ".txt";

    bool flag = CrowHelper::getPart(msg, "command") == "отправить";
    std::thread t(threadSender, letter,
                  file::Path::touchFolder("print").value() + fileName, flag);
    t.detach();

    return dom::UrlWrapper::toHTMLHref("print/" + fileName);
}

void
mult::MailSender::threadSender(const Letter& aLetter,
                               const std::string& aFileName,
                               bool aRealSend) noexcept
{
    std::ofstream out(aFileName);

    auto table  = file::File::getTable(aLetter.data, file::FileType::String);
    auto letter = sliseText(aLetter.text, *table.begin());


    if (!aRealSend)
    {
        out << "Включён тестовый режим.\nОтправка писем не производится\n";
        out << "\n-------------------------------------------------\n";
        out << std::endl;
    }

    dom::Mail mail(aLetter.login, aLetter.password);
    for (auto& row : table)
    {
        std::string copy;
        for (auto& l : letter)
        {
            copy += l.second + row[l.first];
        }

        if (aRealSend)
        {
            if (mail.send(row["$mail$"], aLetter.theme, copy))
            {
                out << "Отправка по адресу " + row["$mail$"] +
                           " прошла успешко.";
            }
            else
            {
                out << "--> Ошибка отправки  по адресу " + row["$mail$"] + "!";
            }
        }
        else
        {
            out << "Адрес: " + row["$mail$"] + "\n";
            out << "Тема: " + aLetter.theme + "\n\n";
            out << "Текст письма:\n " + copy + "\n";
            out << "\n-------------------------------------------------\n\n";
        }
        out << std::endl;
    }
    out << "Рассылка писем завершена в " + dom::DateAndTime::getCurentTime() +
               ".";
    out << std::endl;
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
