#ifndef POST_ROUTER_HPP
#define POST_ROUTER_HPP

#include <unordered_map>

#include "post_handler.hpp"

namespace post
{
struct PostRouter
{

    static std::unordered_map<
        str::String,
        decltype(&post::PostHandler::postSubrouter<post::PostHandler,
                                                   data::Dummy>)>
        mProcessRouter;
    static std::unordered_map<str::String,
                              decltype(&post::PostHandler::drop<data::Dummy>)>
        mDropRouter;
    static std::unordered_map<
        str::String,
        decltype(&post::PostHandler::rawDataHandler<data::Dummy>)>
        mRawDataRouter;

    template <typename... Args>
    static auto processRouter(const char* aName, Args&&... args)
    {
        decltype(mProcessRouter.begin()->second(
            std::forward<Args>(args)...)) result;
        auto it = mProcessRouter.find(aName);
        if (it != mProcessRouter.end())
            result = it->second(std::forward<Args>(args)...);
        return result;
    }

    template <typename... Args>
    static auto dropRouter(const char* aName, Args&&... args)
    {
        decltype(mDropRouter.begin()->second(
            std::forward<Args>(args)...)) result;
        auto it = mDropRouter.find(aName);
        if (it != mDropRouter.end())
            result = it->second(std::forward<Args>(args)...);
        return result;
    }

    template <typename... Args>
    static auto rawDataRouter(const char* aName, Args&&... args)
    {
        decltype(mRawDataRouter.begin()->second(
            std::forward<Args>(args)...)) result;
        auto it = mRawDataRouter.find(aName);
        if (it != mRawDataRouter.end())
            result = it->second(std::forward<Args>(args)...);
        return result;
    }
};

}; // namespace post

#endif // !POST_ROUTER_HPP
