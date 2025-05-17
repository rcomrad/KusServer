#ifndef ROUTER_NODE_HPP
#define ROUTER_NODE_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

//--------------------------------------------------------------------------------

namespace route
{
class RouterNode
{
public:
    RouterNode(const std::string& aVolumeName,
               const std::string& aNodeName,
               void* aFunc) noexcept;

    RouterNode(const std::vector<std::tuple<std::string, std::string, void*>>&
                   aRouts) noexcept;

    RouterNode(const std::vector<std::string>& aVolumeNames,
               const std::string& aNodeName,
               const std::vector<void*>& aFuncs) noexcept;

    // RouterNode(const std::string& aVolumeName,
    //            const std::unordered_set<std::string>& aNodeNames,
    //            void* aFunc) noexcept;

    // RouterNode(const std::string& aVolumeName,
    //            const std::unordered_map<std::string, void*>& aNodes)
    //            noexcept;
};
} // namespace route

//--------------------------------------------------------------------------------

#endif // !ROUTER_NODE_HPP
