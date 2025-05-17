#include "router_master.hpp"

//--------------------------------------------------------------------------------

route::RouterMaster&
route::RouterMaster::getInstance() noexcept
{
    static RouterMaster instance;
    return instance;
}

//--------------------------------------------------------------------------------

// TODO: is it possable to move string into map?
void
route::RouterMaster::add(const std::string& aRouterName,
                         const std::unordered_set<std::string>& aNodeNames,
                         std::function<void*()>&& aFunc) noexcept
{
    getInstance().addNonstatic(aRouterName, aNodeNames, std::move(aFunc));
}

void
route::RouterMaster::addNonstatic(
    const std::string& aRouterName,
    const std::unordered_set<std::string>& aNodeNames,
    std::function<void*()>&& aFunc)
{
    auto& cell = mMemory[aRouterName];
    for (auto& name : aNodeNames)
    {
        cell[name] = std::move(aFunc);
    }
}

//--------------------------------------------------------------------------------
