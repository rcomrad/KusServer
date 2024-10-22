#pragma once

#include <boost/optional/optional.hpp>

#include <string>
#include <string_view>
#include <unordered_map>

#include "core/logging/logging.hpp"

#include "./nodes/node.hpp"

// #include "core/logging/logging.hpp"

// #include "command.hpp"
// #include "relation.hpp"

namespace onto
{

class WebBase
{
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
    template <typename Res = Node>
    boost::optional<Res&> get_node(
        const std::string_view& a_name) const noexcept
    {
        auto it = m_storage.find(a_name);
        boost::optional<Res&> result;
        if (it != m_storage.end())
        {
            result = *dynamic_cast<Res*>(it->second);
        }
        else
        {
            LOG_WARNING("No '%s' node.", a_name);
        }
        return result;
    }

    std::string print() const noexcept;

protected:
    void registrateNode(const std::string_view& a_name, Node& a_obj) noexcept;

private:
    std::unordered_map<std::string_view, Node*> m_storage;
};

} // namespace onto
