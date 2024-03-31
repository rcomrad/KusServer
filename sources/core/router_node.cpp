#include "router_node.hpp"

#include "router_map.hpp"

route::RouterNode::RegistrateCallBack(const str::string& aVolumeName,
                              const str::string& aNodeName,
                              void* aFunc) noexcept
{
    CallBackStorage::add(aVolumeName, aNodeName, aFunc);
}

// route::RouterNode::RouterNode(
//     const std::vector<std::tuple<str::string, str::string, void*>>&
//         aRouts) noexcept
// {
//     for (const auto& i : aRouts)
//     {
//         RouterMap::add(std::get<0>(i), std::get<1>(i), std::get<2>(i));
//     }
// }

// route::RouterNode::RouterNode(const std::vector<str::string>& aVolumeNames,
//                               const str::string& aNodeName,
//                               const std::vector<void*>& aFuncs) noexcept
// {
//     // TODO: other vector size check
//     for (int i = 0; i < aVolumeNames.size(); ++i)
//     {
//         RouterMap::add(aVolumeNames[i], aNodeName, aFuncs[i]);
//     }
// }

// route::RouterNode::RouterNode(const str::string& aVolumeName,
//                               const std::unordered_set<str::string>&
//                               aNodeNames, void* aFunc) noexcept
// {
//     for(const auto& name : aNodeNames)
//     {
//         RouterMap::add(aVolumeName, );
//     }
//     RouterMaster::add(aRouterName, aNodeNames, std::move(aFunc));
// }
// route::RouterNode::RouterNode(
//     const str::string& aVolumeName,
//     const std::unordered_map<str::string, void*>& aNodes) noexcept
// {
//     // RouterMaster::add(aRouterName, aNodeNames, std::move(aFunc));
// }
