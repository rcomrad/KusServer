#include "request_unpacker.hpp"

boost::optional<const char*>
serv::RequestUnpacker::getToken(const crow::request& aReq) noexcept
{
    boost::optional<const char*> result;
    auto it = aReq.headers.find("token");
    if (it != aReq.headers.end())
    {
        result = it->second;
    }
    return result;
}

boost::optional<const char*>
serv::RequestUnpacker::getPart(const crow::multipart::message& aMsg,
                               str::String aStr) noexcept
{
    boost::optional<const char*> result;
    auto it = aMsg.part_map.find(aStr);
    if (it != aMsg.part_map.end())
    {
        result = it->second.body;
    }
    return result;
}

const char*
serv::RequestUnpacker::getPartUnsafe(const crow::multipart::message& aMsg,
                                     str::String aStr) noexcept
{
    static const str::String emptyStr = "";
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
