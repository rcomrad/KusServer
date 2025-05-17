#ifndef MAIL_SENDER_HPP
#define MAIL_SENDER_HPP

#include <string>

#include "crow.h"

//--------------------------------------------------------------------------------

namespace mult
{

class MailSender
{
public:
    static str::String process(const crow::request& aReq) noexcept;

private:
    struct Letter
    {
        str::String theme;
        str::String text;
        str::String login;
        str::String password;
        str::String data;
    };

    static void threadSender(Letter aLetter,
                             str::String aFileName,
                             bool aRealSend) noexcept;

    static std::vector<std::pair<str::String, str::String>> sliseText(
        const char* aText,
        const std::unordered_map<str::String, str::String>& aKeys) noexcept;
};

} // namespace mult

//--------------------------------------------------------------------------------

#endif // !MAIL_SENDER_HPP
