#pragma once

#include <string>
#include <string_view>

#include "web_nodes.hpp"

namespace onto
{

class Web : public WebNodes
{
public:
    Web() noexcept;

    void applyDump(std::string&& a_dump) noexcept;
    void applyData(const std::string& a_data) noexcept;

private:
    // template <typename T>
    // void populate(NodeContainer<T>& a_storage,
    //               const std::unordered_set<std::string_view>& a_names)
    //               noexcept
    // {
    //     for (const auto& name : a_names)
    //     {
    //         Command c;
    //         c.m_name = name;
    //         createNode(a_storage, c);
    //     }
    // }

    // template <typename T, typename... Args>
    // T& createNode(NodeContainer<T>& a_storage, Args... args) noexcept
    // {
    //     auto it = a_storage.emplace(a_command.m_name, T(args...)).first;
    //     m_storage[it->first] = dynamic_cast<Node*>(&it->second);
    //     return it->second;
    // }

}; // namespace onto

} // namespace onto
