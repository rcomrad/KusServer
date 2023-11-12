#ifndef ROUTER_MASTER_HPP
#define ROUTER_MASTER_HPP

//--------------------------------------------------------------------------------

#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "domain/holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace route
{
class RouterMaster
{
public:
    HOLY_TRINITY_SINGLE(RouterMaster);

private:
    RouterMaster() noexcept = default;
    static RouterMaster& getInstance() noexcept;

    //----------------------------------------------------------------------------

public:
    static void add(const std::string& aRouterName,
                    const std::unordered_set<std::string>& aNodeNames,
                    std::function<void*()>&& aFunc) noexcept;

private:
    void addNonstatic(const std::string& aRouterName,
                      const std::unordered_set<std::string>& aNodeNames,
                      std::function<void*()>&& aFunc) noexcept;

    //----------------------------------------------------------------------------

public:
    template <typename T>
    static void applyRoutes(
        const std::string& aRouterName,
        std::unordered_map<std::string, T*>& aRouter) noexcept;

private:
    template <typename T>
    void applyRoutesNonstatic(
        const std::string& aRouterName,
        std::unordered_map<std::string, T*>& aRouter) const noexcept
    {
        auto cellIt = mMemory.find(aRouterName);
        if (cellIt != mMemory.end())
        {
            for (auto& r : cellIt->second)
            {
                aRouter[r.first] = (T*)r.second();
            }
        }
    }

    //----------------------------------------------------------------------------

private:
    std::unordered_map<std::string,
                       std::unordered_map<std::string, std::function<void*()>>>
        mMemory;
};
} // namespace route

//--------------------------------------------------------------------------------

#endif // !ROUTER_MASTER_HPP
