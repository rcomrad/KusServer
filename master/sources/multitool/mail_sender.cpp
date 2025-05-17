#include "mail_sender.hpp"

#include <thread>

#include "domain/date_and_time.hpp"
#include "domain/mail.hpp"
#include "domain/url_wrapper.hpp"

#include "file_data/file.hpp"
#include "file_data/parser.hpp"
#include "file_data/path.hpp"
#include "post/post_handler.hpp"
#include "server/request_unpacker.hpp"
// TODO: crow::multipart::message

std::string
mult::MailSender::process(const crow::request& aReq) noexcept
{
    crow::multipart::message msg(aReq);

    Letter letter;
    letter.theme    = serv::RequestUnpacker::getPartUnsafe(msg, "theme");
    letter.text     = serv::RequestUnpacker::getPartUnsafe(msg, "text");
    letter.login    = serv::RequestUnpacker::getPartUnsafe(msg, "login");
    letter.password = serv::RequestUnpacker::getPartUnsafe(msg, "password");
    letter.data     = serv::RequestUnpacker::getPartUnsafe(msg, "data");

    std::string result;
    if (letter.theme.empty())
    {
        result = "Укажите тему для отправляемых писем.";
    }
    else if (letter.login.empty())
    {
        result =
            "Укажите логин почты с которой будет происходить рассылка писем.";
    }
    else if (letter.password.empty())
    {
        result =
            "Укажите пароль почты с которой будет происходить рассылка писем.";
    }
    else if (letter.text.empty())
    {
        result = "Укажите текст письма для рассылки.";
    }
    else if (letter.data.empty())
    {
        result = "Прикрепите файл с адресантами рассылки и их данными.";
    }
    else
    {
        auto name = dom::DateAndTime::getCurentTimeSafe();
        file::File::writeData(name + ".xlsx", letter.data);
        system((file::Path::getPathUnsafe("to_csv.sh") + " "s + name +
                ".xlsx " + name + ".csv")
                   .c_str());
        letter.data = file::File::getAllData(name + ".csv");
        // letter.data =
        //     file::File::getAllData(letter.data, file::FileType::String);

        std::string fileName =
            "mail_report_" + dom::DateAndTime::getCurentTimeSafe() + ".txt";

        bool flag =
            serv::RequestUnpacker::getPartUnsafe(msg, "command") == "отправить";
        std::thread t(threadSender, letter,
                      file::Path::touchFolder("print").value() + fileName,
                      flag);
        t.detach();

        if (flag)
        {
            result = "Производится рассылка писем. <br>"
                     "Чтобы увидеть отчёт по рассылке, <br>"
                     "нажмите колесиком мыши на " +
                     dom::UrlWrapper::toHTMLHref("print/" + fileName) +
                     ".<br>"
                     "Файл откроется в новой вкладке.<br>"
                     " Сохраните открытый в новой вкладке отчет чтобы он "
                     "стал удобочитаемый<br>"
                     "(щелкнуть правой кнопкой мыши -> сохранить как).";
        }
        else
        {
            result =
                "Включён тестовый режим рассылке (письма не отправляются). <br>"
                "Чтобы увидеть отчёт по рассылке, <br>"
                "нажмите колесиком мыши на " +
                dom::UrlWrapper::toHTMLHref("print/" + fileName) +
                ".<br>"
                "Файл откроется в новой вкладке.<br>"
                " Сохраните открытый в новой вкладке отчет чтобы он "
                "стал удобочитаемый<br>"
                "(щелкнуть правой кнопкой мыши -> сохранить как).";
        }
    }

    return result;
}
#include <set>
void
mult::MailSender::threadSender(Letter aLetter,
                               std::string aFileName,
                               bool aRealSend) noexcept
{
    std::ofstream out(aFileName);

    auto table =
        file::File::getTable(aLetter.data, file::FileType::String,
                             [](char c)
                             {
                                 return c == ';' || c == ',' || c == '\0';
                                 ;
                             });

    std::unordered_map<std::string,
                       std::unordered_map<std::string, std::string>*>
        mmm;
    for (auto& i : table)
    {
        auto it = mmm.find(i["$mail$"]);
        if (it == mmm.end())
        {
            it = mmm.insert({i["$mail$"], &i}).first;
        }
        else
        {
            i.erase("$mail$");
        }

        std::set<std::string> q;
        for (auto& k : i)
        {
            if (k.first == "$mail$") continue;
            q.insert(k.first);
        }

        for (auto& j : q)
        {
            (*(it->second))["$all$"] += j + ": " + i[j] + " \t ";
        }
        (*(it->second))["$all$"].push_back('\n');
    }

    for (auto& i : table)
        i["$all$"] = file::Parser::slice(i["$all$"], "", "\"")[0];

    auto letter = sliseText(aLetter.text, *table.begin());

    if (!aRealSend)
    {
        out << "Включён тестовый режим.\nОтправка писем не производится\n";
        out << "\n-------------------------------------------------\n";
        out << std::endl;
    }
    else
    {
        out << "Старт рассылки\n";
        out << "\n-------------------------------------------------\n";
        out << std::endl;
    }

    dom::writeInfo("Start sending");
    dom::Mail mail(aLetter.login, aLetter.password);
    for (auto& row : table)
    {
        auto temp = row.find("$mail$");
        if (temp == row.end())
        {
            out << "--> отсутствует адрес электронной почты!\n";
            continue;
        }
        auto addr = temp->second;

        // dom::writeInfo("Sending to:", row["$mail$"]);
        std::string copy;
        for (auto& l : letter)
        {
            copy += l.second + row[l.first];
        }

        // dom::writeInfo("Theme is:", aLetter.theme);
        // dom::writeInfo("Text is:", copy);
        if (aRealSend)
        {
            bool success = false;
            for (int i = 0; i < 2; ++i)
            {
                success = mail.send(addr, aLetter.theme, copy);
                if (success || i == 1) break;

                out << "Однаминутный перерыв на чай начался в " +
                           dom::DateAndTime::getCurentTime() + "."
                    << std::endl;
                std::this_thread::sleep_for(60000ms);
                out << "Однаминутный перерыв на чай завершился в " +
                           dom::DateAndTime::getCurentTime() + "."
                    << std::endl;
            }
            if (success)
            {
                out << "Отправка по адресу " + addr + " прошла успешно.";
            }
            else
            {
                out << "-->ERROR: Ошибка отправки  по адресу " + addr + "!";
            }
        }
        else
        {
            out << "Адрес: " + addr + "\n";
            out << "Тема: " + aLetter.theme + "\n\n";
            out << "Текст письма:\n " + copy + "\n";
            out << "\n-------------------------------------------------\n\n";
        }
        out << std::endl;
    }
    dom::writeInfo("Finish sending");

    if (aRealSend)
    {
        out << "Рассылка писем завершена в " +
                   dom::DateAndTime::getCurentTime() + "."
            << std::endl;
    }
}

std::vector<std::pair<std::string, std::string>>
mult::MailSender::sliseText(
    const std::string& aText,
    const std::unordered_map<std::string, std::string>& aKeys) noexcept
{
    dom::writeInfo("Start parsing letter");
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

    dom::writeInfo("Finished parsing letter");

    return result;
}
