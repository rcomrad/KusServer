#ifndef GET_ROUTER_HPP
#define GET_ROUTER_HPP

#include <unordered_map>

#include "get_handler.hpp"

namespace get
{
class GetRouter
{
public:
    template <typename... Args>
    static crow::json::wvalue basicRouter(const std::string& aTableName,
                                          Args&&... args) noexcept
    {
        crow::json::wvalue result;
        auto it = mBasicRouterMap.find(aTableName);
        if (it != mBasicRouterMap.end()) result = it->second(args...);
        return result;
    }

    template <typename... Args>
    static crow::json::wvalue dumpRouter(const std::string& aTableName,
                                         Args&&... args) noexcept
    {
        crow::json::wvalue result;
        auto it = mDumpRouterMap.find(aTableName);
        if (it != mDumpRouterMap.end()) result = it->second(args...);
        return result;
    }

private:
    static std::unordered_map<std::string,
                              decltype(&get::GetHandler::process<data::Dummy>)>
        mBasicRouterMap;
    static std::unordered_map<std::string,
                              decltype(&get::GetHandler::dump<data::Dummy>)>
        mDumpRouterMap;
};

} // namespace get
#endif // !GET_ROUTER
