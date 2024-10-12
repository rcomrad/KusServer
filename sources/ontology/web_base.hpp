#pragma once

#include <boost/optional/optional.hpp>

#include <string>
#include <string_view>
#include <unordered_map>

#include "core/logging/logging.hpp"

namespace onto
{

class Node;

class WebBase
{
public:
    template <typename Res = Node>
    Res* searchNode(const std::string_view& a_name) const noexcept
    {
        Res* result = nullptr;
        auto it     = m_storage.find(a_name);
        if (it != m_storage.end())
        {
            result = dynamic_cast<Res*>(it->second);
        }
        else
        {
            LOG_WARNING("No '%s' node.", a_name);
        }
        return result;
    }

    std::string print() const noexcept;
    void clearNotUsedNodes() noexcept;

protected:
    void registrateNode(const std::string_view& a_name, Node& a_obj) noexcept;

private:
    std::unordered_map<std::string_view, Node*> m_storage;
};

} // namespace onto
