#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include "../relation.hpp"

namespace onto
{

struct Node
{
    enum Kind
    {
        NUN,
        TYPE,
        FUNCTION,
        VARIABLE,
        OPERATOR,
        EXPRESSION,
        MAX
    };

    Node(Kind a_kind, const std::string_view& a_name) noexcept;
    virtual ~Node() = default;

    Kind getKind() const noexcept;
    const std::string& getName() const noexcept;

    void addNeighbor(Node& a_node, Relation a_relation) noexcept;

private:
    Kind m_kind;
    std::string m_name;

    std::unordered_set<Node*> m_neighbor[RELATION_COUNT * 2];
};

} // namespace onto
