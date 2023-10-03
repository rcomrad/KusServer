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
    static std::string process(const crow::request& aReq) noexcept;

private:
    static std::vector<std::pair<std::string, std::string>> sliseText(
        const std::string& aText,
        const std::unordered_map<std::string, std::string>& aKeys) noexcept;
};

} // namespace mult

//--------------------------------------------------------------------------------

#endif // !MAIL_SENDER_HPP
