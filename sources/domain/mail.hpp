#ifndef MAIL_HPP
#define MAIL_HPP

//--------------------------------------------------------------------------------

#include <string>

//--------------------------------------------------------------------------------

namespace dom
{

class Mail
{
public:
    Mail(const std::string& aLogin    = "",
         const std::string& aPassword = "") noexcept;

    bool send(const std::string& aEmailName,
              const std::string& aTheme,
              const std::string& aText) const noexcept;

private:
    std::string mLogin;
    std::string mPassword;
};

} // namespace dom

//--------------------------------------------------------------------------------

#endif // !MAIL_HPP
