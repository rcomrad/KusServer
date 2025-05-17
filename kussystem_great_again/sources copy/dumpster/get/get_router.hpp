#ifndef GET_ROUTER_HPP
#define GET_ROUTER_HPP

#include <unordered_map>

#include "get_handler.hpp"

namespace get
{
struct GetRouter
{

    static std::unordered_map<str::String,
                              decltype(&get::GetHandler::process<data::Dummy>)>
        mBasicRouter;
    static std::unordered_map<str::String,
                              decltype(&get::GetHandler::dump<data::Dummy>)>
        mDumpRouter;
    static std::unordered_map<str::String, std::vector<str::String>>
        mColumnNamesRouter;

    template <typename... Args>
    static auto basicRouter(const char* aName, Args&&... args)
    {
        decltype(mBasicRouter.begin()->second(
            std::forward<Args>(args)...)) result;
        auto it = mBasicRouter.find(aName);
        if (it != mBasicRouter.end())
            result = it->second(std::forward<Args>(args)...);
        return result;
    }

    template <typename... Args>
    static auto dumpRouter(const char* aName, Args&&... args)
    {
        decltype(mDumpRouter.begin()->second(
            std::forward<Args>(args)...)) result;
        auto it = mDumpRouter.find(aName);
        if (it != mDumpRouter.end())
            result = it->second(std::forward<Args>(args)...);
        return result;
    }

    static std::vector<str::String>& columnNamesRouter(const char* aName);
};

}; // namespace get

#endif // !GET_ROUTER_HPP
