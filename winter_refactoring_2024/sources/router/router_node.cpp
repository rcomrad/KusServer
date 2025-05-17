#include "router_node.hpp"

#include "router_map.hpp"

route::RouterNode::RouterNode(const std::string& aVolumeName,
                              const std::string& aNodeName,
                              void* aFunc) noexcept
{
    RouterMap::add(aVolumeName, aNodeName, aFunc);
}

route::RouterNode::RouterNode(
    const std::vector<std::tuple<std::string, std::string, void*>>&
        aRouts) noexcept
{
    for (const auto& i : aRouts)
    {
        RouterMap::add(std::get<0>(i), std::get<1>(i), std::get<2>(i));
    }
}

route::RouterNode::RouterNode(const std::vector<std::string>& aVolumeNames,
                              const std::string& aNodeName,
                              const std::vector<void*>& aFuncs) noexcept
{
    // TODO: other vector size check
    for (int i = 0; i < aVolumeNames.size(); ++i)
    {
        RouterMap::add(aVolumeNames[i], aNodeName, aFuncs[i]);
    }
}

// route::RouterNode::RouterNode(const std::string& aVolumeName,
//                               const std::unordered_set<std::string>&
//                               aNodeNames, void* aFunc) noexcept
// {
//     for(const auto& name : aNodeNames)
//     {
//         RouterMap::add(aVolumeName, );
//     }
//     RouterMaster::add(aRouterName, aNodeNames, std::move(aFunc));
// }
// route::RouterNode::RouterNode(
//     const std::string& aVolumeName,
//     const std::unordered_map<std::string, void*>& aNodes) noexcept
// {
//     // RouterMaster::add(aRouterName, aNodeNames, std::move(aFunc));
// }
