#include "router_node.hpp"

#include "router_master.hpp"

route::RouterNode::RouterNode(const std::string& aRouterName,
                              const std::unordered_set<std::string>& aNodeNames,
                              std::function<void*()>&& aFunc) noexcept
{
    RouterMaster::add(aRouterName, aNodeNames, std::move(aFunc));
}
