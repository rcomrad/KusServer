#include "mail.hpp"

#include <mailio/mailboxes.hpp>
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>

#include "domain/log.hpp"

#include "file_data/file.hpp"

dom::Mail::Mail(const char* aLogin, const char* aPassword) noexcept
    : mLogin(aLogin), mPassword(aPassword)
{
    if (aLogin.find("adtspb") != str::String::npos)
    {
        adtSmtp();
        LOG_INFO(0, "act");
    }
    else
    {
        academtalantTls();
        LOG_INFO(0, "at");
    }

    LOG_INFO(mSmtp, mPort);
}

void
dom::Mail::useDefaultMail() noexcept
{
    static auto pass = file::File::getWords("config", "mail.pass");
    mLogin           = pass[0][0];
    mPassword        = pass[0][1];
    LOG_INFO(0, mLogin);
    LOG_INFO(0, mPassword);
    academtalantTls();
}

void
dom::Mail::adtSmtp() noexcept
{
    mSmtp    = "smtp.yandex.com";
    mPort    = 465;
    mMetchod = mailio::smtps::auth_method_t::LOGIN;
}

void
dom::Mail::academtalantTls() noexcept
{
    mSmtp    = "mail.academtalant.ru";
    mPort    = 587;
    mMetchod = mailio::smtps::auth_method_t::START_TLS;
}

bool
dom::Mail::send(const char* aEmailName,
                const char* aTheme,
                const char* aText) const noexcept
{
    bool result = true;

    try
    {
        mailio::message msg;
        msg.header_codec(mailio::message::header_codec_t::BASE64);
        msg.from(mailio::mail_address("KusSystem",
                                      mLogin)); // set the correct sender
                                                // name and address
        msg.add_recipient(
            mailio::mail_address("", aEmailName)); // set the correct recipent
                                                   // name and address
        msg.subject(aTheme);

        msg.content_transfer_encoding(
            mailio::mime::content_transfer_encoding_t::QUOTED_PRINTABLE);
        msg.content_type(mailio::message::media_type_t::TEXT, "plain", "utf-8");

        msg.content(aText);

        mailio::smtps conn(mSmtp, mPort);
        mailio::dialog_ssl::ssl_options_t temp;
        temp.verify_mode = boost::asio::ssl::verify_none;
        temp.method      = boost::asio::ssl::context::sslv23;
        conn.ssl_options(temp);
        conn.authenticate(mLogin, mPassword, mMetchod);
        conn.submit(msg);
    }
    catch (mailio::smtp_error& exc)
    {
        LOG_ERROR(1, exc.what());
        result = false;
    }
    catch (mailio::dialog_error& exc)
    {
        LOG_ERROR(2, exc.what());
        result = false;
    }

    return result;
}

// using mailio::dialog_error;
// using mailio::mail_address;
// using mailio::message;
// using mailio::mime;
// using mailio::smtp_error;
// using mailio::smtps;
// using std::cout;
// using std::endl;
// using str::String;

// int
// main()
// {
//     std::ifstream inp("text.txt");
//     str::String text;

//     std::getline(inp, text, '\0');
//     inp.close();

//     inp.open("data.txt");

//     int cnt = 0;
//     str::String email, name, pass;
//     while (inp >> email)
//     {
//         cnt++;
//         bool flag = true;
//         while (flag)
//         {
//             flag = false;
//             std::cout << cnt << " " << email << "\n";

//             if (email.find('@') == -1)
//             {
//                 std::cout << "email error\n";
//                 break;
//             }

//             try
//             {
//                 message msg;
//                 msg.header_codec(message::header_codec_t::BASE64);
//                 msg.from(mail_address(
//                     "",
//                     "fedorovas@adtspb.ru")); // set the correct sender
//                                              // name and address
//                 msg.add_recipient(
//                     mail_address("", email)); // set the correct recipent
//                                               // name and address
//                 msg.subject("Итоги заключительного этапа городского тура "
//                             "олимпиады по информатике");

//                 msg.content_transfer_encoding(
//                     mime::content_transfer_encoding_t::QUOTED_PRINTABLE);
//                 msg.content_type(message::media_type_t::TEXT, "plain",
//                 "utf-8");

//                 str::String temp = text;

//                 // temp += "\nЛогин: " + name + "\n";
//                 // temp += "Пароль: " + pass + "\n";

//                 // temp += "\nС уважением, Федоров Александр Сергеевич.";

//                 msg.content(temp);

//                 smtps conn("smtp.yandex.com", 465);
//                 conn.authenticate("fedorovas@adtspb.ru", "8620yan",
//                                   smtps::auth_method_t::LOGIN);
//                 conn.submit(msg);
//             }
//             catch (smtp_error& exc)
//             {
//                 cout << exc.what() << endl;
//                 flag = true;
//             }
//             catch (dialog_error& exc)
//             {
//                 cout << exc.what() << endl;
//                 flag = true;
//             }

//             if (flag)
//             {
//                 // char c;
//                 // std::cin >> c;

//                 int rrr = 0;
//                 for (int i = 0; i < 1e6; ++i)
//                 {
//                     rrr += rand();
//                 }
//                 std::cout << rrr << std::endl;
//             }
//         }
//     }
// }
