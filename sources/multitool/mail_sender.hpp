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
};

} // namespace mult

//--------------------------------------------------------------------------------

#endif // !MAIL_SENDER_HPP
