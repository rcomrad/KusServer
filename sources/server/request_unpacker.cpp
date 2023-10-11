#include "request_unpacker.hpp"

boost::optional<const std::string&>
serv::RequestUnpacker::getToken(const crow::request& aReq) noexcept
{
    boost::optional<const std::string&> result;
    auto it = aReq.headers.find("token");
    if (it != aReq.headers.end())
    {
        result = it->second;
    }
    return result;
}
