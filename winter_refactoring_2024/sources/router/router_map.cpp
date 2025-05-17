#include "router_map.hpp"

//--------------------------------------------------------------------------------

route::RouterMap&
route::RouterMap::getInstance() noexcept
{
    static RouterMap instance;
    return instance;
}

//--------------------------------------------------------------------------------

void
route::RouterMap::add(const std::string& aVolumeName,
                      const std::string& aNodeName,
                      void* aFunc) noexcept
{
    getInstance().addNonstatic(aVolumeName, aNodeName, aFunc);
}

void*
route::RouterMap::get(const std::string& aVolumeName,
                      const std::string& aNodeName) noexcept
{
    return getInstance().getNonstatic(aVolumeName, aNodeName);
}

//--------------------------------------------------------------------------------

void
route::RouterMap::addNonstatic(const std::string& aVolumeName,
                               const std::string& aNodeName,
                               void* aFunc) noexcept
{
    mMap[aVolumeName][aNodeName] = aFunc;
}

void*
route::RouterMap::getNonstatic(const std::string& aVolumeName,
                               const std::string& aNodeName) const noexcept
{
    void* result = nullptr;

    auto it1 = mMap.find(aVolumeName);
    if (it1 != mMap.end())
    {
        auto it2 = it1->second.find(aNodeName);
        if (it2 != it1->second.end())
        {
            // TODO: warning? info?
            it2 = it1->second.find("*");
        }

        if (it2 != it1->second.end())
        {
            result = it2->second;
        }
        else
        {
            // TODO: error!
        }
    }
    else
    {
        // TODO: error!
    }

    return result;
}

//--------------------------------------------------------------------------------

// TODO: is it possable to move string into map?
// void
// route::RouterMaster::add(const std::string& aRouterName,
//                          const std::unordered_set<std::string>& aNodeNames,
//                          std::function<void*()>&& aFunc) noexcept
// {
//     getInstance().addNonstatic(aRouterName, aNodeNames, std::move(aFunc));
// }

// void
// route::RouterMaster::addNonstatic(
//     const std::string& aRouterName,
//     const std::unordered_set<std::string>& aNodeNames,
//     std::function<void*()>&& aFunc)
// {
//     auto& cell = mMemory[aRouterName];
//     for (auto& name : aNodeNames)
//     {
//         cell[name] = std::move(aFunc);
//     }
// }

//--------------------------------------------------------------------------------
