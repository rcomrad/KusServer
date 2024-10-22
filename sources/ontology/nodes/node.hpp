#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include "../relation.hpp"

namespace onto
{

constexpr int NEIGHBOR_SIZE = RELATION_COUNT * 2;

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

    std::string print() const noexcept;

private:
    Kind m_kind;
    std::string m_name;

    std::unordered_set<Node*> m_neighbor[NEIGHBOR_SIZE];

    size_t print(char* a_buffer, size_t a_cnt) const noexcept;
};

} // namespace onto
