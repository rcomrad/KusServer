#include "mail.hpp"

#include <mailio/mailboxes.hpp>
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>

#include "general_tools/log.hpp"
#include "text_data/file.hpp"

dom::Mail::Mail(const std::string& aLogin,
                const std::string& aPassword) noexcept
    : mLogin(aLogin), mPassword(aPassword)
{
    if (aLogin.find("adtspb") != std::string::npos)
    {
        adtSmtp();
    }
    else
    {
        academtalantTls();
    }

    LOG_INFO(mSmtp, mPort);
}

void
dom::Mail::useDefaultMail() noexcept
{
    static auto pass = text::File::getWords("config", "mail.pass");
    mLogin           = pass[0][0];
    mPassword        = pass[0][1];

    adtSmtp();
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
dom::Mail::send(const std::string& aEmailName,
                const std::string& aTheme,
                const std::string& aText) const noexcept
{
    bool result = true;

    try
    {
        mailio::message msg;
        msg.header_codec(mailio::message::header_codec_t::BASE64);
        msg.from(mailio::mail_address("", mLogin)); // set the correct sender
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
        conn.authenticate(mLogin, mPassword, mMetchod);
        conn.submit(msg);
    }
    catch (mailio::smtp_error& exc)
    {
        LOG_ERROR(exc.what());
        result = false;
    }
    catch (mailio::dialog_error& exc)
    {
        LOG_ERROR(exc.what());
        result = false;
    }

    return result;
}
