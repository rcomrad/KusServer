#pragma once

#include <boost/optional/optional.hpp>

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

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

    // std::string print() const noexcept;
    // void clearNotUsedNodes() noexcept;

protected:
    void registrateNode(const std::string_view& a_name, Node& a_obj);

    template <typename T>
    void clearNotUsedNodes(T& a_storage) noexcept
    {
        std::vector<const std::string*> to_delete;
        for (auto& i : a_storage)
        {
            if (i.second.isLonelyNode())
            {
                to_delete.emplace_back(&i.first);
            }
        }

        for (auto& i : to_delete)
        {
            m_storage.erase(*i);
            a_storage.erase(*i);
        }
    }

private:
    std::unordered_map<std::string_view, Node*> m_storage;
};

} // namespace onto
