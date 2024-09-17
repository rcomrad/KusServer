#pragma once

#include <boost/optional/optional.hpp>

#include <string>
#include <string_view>
#include <unordered_map>

#include "./nodes/node.hpp"

// #include "core/logging/logging.hpp"

// #include "command.hpp"
// #include "relation.hpp"

namespace onto
{

class WebBase
{
private:
    template <class T>
    using NodeContainer = std::unordered_map<std::string, T>;

    // static std::string_view getNodeName(const Command& a_command) noexcept
    // {
    //     return a_command.m_name;
    // }
    // static std::string_view getNodeName(const std::string_view& a_name)
    // noexcept
    // {
    //     return a_name;
    // }

public:
    boost::optional<Node&> get_node(
        const std::string_view& a_name) const noexcept;

protected:
    template <typename T, typename... Args>
    T& createNode(NodeContainer<T> a_storage,
                  const std::string_view& a_name,
                  Args... args) noexcept
    {
        auto it              = a_storage.emplace(a_name, args).first;
        m_storage[it->first] = dynamic_cast<Node*>(&it->second);
        return it->second;
    }

private:
    std::unordered_map<std::string_view, Node*> m_storage;
};

} // namespace onto
