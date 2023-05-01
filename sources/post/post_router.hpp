#ifndef POST_ROUTER_HPP
#define POST_ROUTER_HPP

#include <unordered_map>

#include "post_handler.hpp"

namespace post
{
class PostRouter
{
public:
    template <typename... Args>
    static crow::json::wvalue basicRouter(const std::string& aTableName,
                                          Args&&... args) noexcept
    {
        crow::json::wvalue result;
        auto it = mPostRouterMap.find(aTableName);
        if (it != mPostRouterMap.end()) result = it->second(args...);
        return result;
    }

    template <typename... Args>
    static crow::json::wvalue dropRouter(const std::string& aTableName,
                                         Args&&... args) noexcept
    {
        crow::json::wvalue result;
        auto it = mDropRouterMap.find(aTableName);
        if (it != mDropRouterMap.end()) result = it->second(args...);
        return result;
    }

    template <typename... Args>
    static crow::json::wvalue rawDataRouter(const std::string& aTableName,
                                            Args&&... args) noexcept
    {
        crow::json::wvalue result;
        auto it = mRawDataRouter.find(aTableName);
        if (it != mRawDataRouter.end()) result = it->second(args...);
        return result;
    }

private:
    static std::unordered_map<
        std::string,
        decltype(&post::PostHandler::process<data::Dummy>)>
        mPostRouterMap;
    static std::unordered_map<std::string,
                              decltype(&post::PostHandler::drop<data::Dummy>)>
        mDropRouterMap;
    static std::unordered_map<
        std::string,
        decltype(&post::PostHandler::rawDataHandler<data::Dummy>)>
        mRawDataRouter;
};

} // namespace post
#endif // !POST_ROUTER
