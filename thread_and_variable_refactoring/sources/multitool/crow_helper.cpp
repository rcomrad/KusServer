#include "crow_helper.hpp"

const std::string&
mult::CrowHelper::getPart(const crow::multipart::message& aMsg,
                          std::string aStr) noexcept
{
    static std::string s = "";
    auto& parts          = aMsg.part_map;
    auto it              = parts.find(aStr);
    if (it != parts.end())
    {
        return it->second.body;
    }
    return s;
}
