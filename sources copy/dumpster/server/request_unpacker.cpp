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

boost::optional<const std::string&>
serv::RequestUnpacker::getPart(const crow::multipart::message& aMsg,
                               std::string aStr) noexcept
{
    boost::optional<const std::string&> result;
    auto it = aMsg.part_map.find(aStr);
    if (it != aMsg.part_map.end())
    {
        result = it->second.body;
    }
    return result;
}

const std::string&
serv::RequestUnpacker::getPartUnsafe(const crow::multipart::message& aMsg,
                                     std::string aStr) noexcept
{
    static const std::string emptyStr = "";
    auto temp                         = getPart(aMsg, aStr);
    if (temp.has_value())
    {
        return temp.value();
    }
    else
    {
        return emptyStr;
    }
}
