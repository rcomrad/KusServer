#ifndef MAIL_HPP
#define MAIL_HPP

//--------------------------------------------------------------------------------

#include <string>

#include <mailio/smtp.hpp>

//--------------------------------------------------------------------------------

namespace dom
{

class Mail
{
public:
    Mail(const std::string& aLogin    = "",
         const std::string& aPassword = "") noexcept;

    void useDefaultMail() noexcept;

    bool send(const std::string& aEmailName,
              const std::string& aTheme,
              const std::string& aText) const noexcept;

private:
    std::string mLogin;
    std::string mPassword;
    std::string mSmtp;
    int mPort;
    mailio::smtps::auth_method_t mMetchod;
};

} // namespace dom

//--------------------------------------------------------------------------------

#endif // !MAIL_HPP
