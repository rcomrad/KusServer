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
class RegistrateCallBack
{
public:
    RegistrateCallBack(const str::string& aVolumeName,
               const str::string& aNodeName,
               void* aFunc) noexcept;

    // RouterNode(const std::vector<std::tuple<str::string, str::string, void*>>&
    //                aRouts) noexcept;

    // RouterNode(const std::vector<str::string>& aVolumeNames,
    //            const str::string& aNodeName,
    //            const std::vector<void*>& aFuncs) noexcept;

    // RouterNode(const str::string& aVolumeName,
    //            const std::unordered_set<str::string>& aNodeNames,
    //            void* aFunc) noexcept;

    // RouterNode(const str::string& aVolumeName,
    //            const std::unordered_map<str::string, void*>& aNodes)
    //            noexcept;
};
} // namespace route

//--------------------------------------------------------------------------------

#endif // !ROUTER_NODE_HPP
