#ifndef ROUTER_NODE_HPP
#define ROUTER_NODE_HPP

//--------------------------------------------------------------------------------

#include <functional>
#include <string>
#include <unordered_set>

//--------------------------------------------------------------------------------

namespace route
{
class RouterNode
{
public:
    RouterNode(const std::string& aRouterName,
               const std::unordered_set<std::string>& aNodeNames,
               std::function<void*()>&& aFunc) noexcept;
};
} // namespace route

//--------------------------------------------------------------------------------

#endif // !ROUTER_NODE_HPP
