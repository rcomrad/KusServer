#ifndef POST_ROUTER_HPP
#define POST_ROUTER_HPP

#include <unordered_map.>

#include "journal_handler.hpp"
#include "mark_handler.hpp"
#include "plan_handler.hpp"
#include "post_handler.hpp"
#include "user_answer_handler.hpp"
#include "user_handler.hpp"

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
        if (it != mPostRouterMap.end())
            result = mPostRouterMap[aTableName](args...);
        return result;
    }

    template <typename... Args>
    static crow::json::wvalue manyToManyRouter(const std::string& aTableName,
                                               Args&&... args) noexcept
    {
        return mManyToManyRouterMap[aTableName](args...);
    }

    template <typename... Args>
    static crow::json::wvalue uploadRouter(const std::string& aTableName,
                                           Args&&... args) noexcept
    {
        return mUploadRouterMap[aTableName](args...);
    }

    template <typename... Args>
    static crow::json::wvalue dropRouter(const std::string& aTableName,
                                         Args&&... args) noexcept
    {
        return mDropRouterMap[aTableName](args...);
    }

private:
    static std::unordered_map<std::string,
                              decltype(&post::PostHandler::process<data::User>)>
        mPostRouterMap;
    static std::unordered_map<
        std::string,
        decltype(&post::PostHandler::manyToMany<data::User>)>
        mManyToManyRouterMap;
    static std::unordered_map<
        std::string,
        decltype(&post::PostHandler::uploadFromFile<data::User>)>
        mUploadRouterMap;
    static std::unordered_map<std::string,
                              decltype(&post::PostHandler::drop<data::User>)>
        mDropRouterMap;
};

} // namespace post
#endif // !POST_ROUTER
