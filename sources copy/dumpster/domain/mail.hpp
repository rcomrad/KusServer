#ifndef MAIL_HPP
#define MAIL_HPP

//--------------------------------------------------------------------------------

#include <mailio/smtp.hpp>

#include <string>

//--------------------------------------------------------------------------------

namespace dom
{

class Mail
{
public:
    Mail(const str::String& aLogin    = "",
         const str::String& aPassword = "") noexcept;

    void useDefaultMail() noexcept;

    bool send(const str::String& aEmailName,
              const str::String& aTheme,
              const str::String& aText) const noexcept;

private:
    str::String mLogin;
    str::String mPassword;
    str::String mSmtp;
    int mPort;
    mailio::smtps::auth_method_t mMetchod;

    void adtSmtp() noexcept;
    void academtalantTls() noexcept;
};

} // namespace dom

//--------------------------------------------------------------------------------

#endif // !MAIL_HPP
