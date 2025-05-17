#ifndef ROUTER_MASTER_HPP
#define ROUTER_MASTER_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "domain/holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace route
{
class RouterMap
{
public:
    HOLY_TRINITY_SINGLE(RouterMap);

    static void add(const std::string& aVolumeName,
                    const std::string& aNodeName,
                    void* aFunc) noexcept;

    static void* get(const std::string& aVolumeName,
                     const std::string& aNodeName) noexcept;

private:
    RouterMap() noexcept = default;
    static RouterMap& getInstance() noexcept;

    void addNonstatic(const std::string& aVolumeName,
                      const std::string& aNodeName,
                      void* aFunc) noexcept;

    void* getNonstatic(const std::string& aVolumeName,
                       const std::string& aNodeName) const noexcept;

    //----------------------------------------------------------------------------

public:
    // static void add(const std::string& aRouterName,
    //                 const std::unordered_set<std::string>& aNodeNames,
    //                 std::function<void*()>&& aFunc) noexcept;

    // private:
    //     void addNonstatic(const std::string& aRouterName,
    //                       const std::unordered_set<std::string>& aNodeNames,
    //                       std::function<void*()>&& aFunc) noexcept;

    //----------------------------------------------------------------------------

    // public:
    //     template <typename T>
    //     static void applyRoutes(
    //         const std::string& aRouterName,
    //         std::unordered_map<std::string, T*>& aRouter) noexcept;

    // private:
    //     template <typename T>
    //     void applyRoutesNonstatic(
    //         const std::string& aRouterName,
    //         std::unordered_map<std::string, T*>& aRouter) const noexcept
    //     {
    //         auto cellIt = mMemory.find(aRouterName);
    //         if (cellIt != mMemory.end())
    //         {
    //             for (auto& r : cellIt->second)
    //             {
    //                 aRouter[r.first] = (T*)r.second();
    //             }
    //         }
    //     }

    //----------------------------------------------------------------------------

private:
    std::unordered_map<std::string, std::unordered_map<std::string, void*>>
        mMap;
};
} // namespace route

//--------------------------------------------------------------------------------

#endif // !ROUTER_MASTER_HPP
