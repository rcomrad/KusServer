#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include "../relation.hpp"

namespace onto
{

// constexpr int NEIGHBOR_SIZE = RELATION_COUNT * 2;

struct Node
{
#define NODE_MACROS(large, default, small) large,
    enum Kind
    {
        NONE,
#include "node.ini"
    };

    Node(Kind a_kind, const std::string_view& a_name) noexcept;
    virtual ~Node() = default;

    Kind getKind() const noexcept;
    const std::string& getName() const noexcept;

    void clearRelationIfExist(Relation a_relation) noexcept;
    void addNeighbor(Node& a_node, Relation a_relation) noexcept;

    std::string print() const noexcept;
    std::string serialize() const noexcept;

    bool isLonelyNode() const noexcept;

private:
    Kind m_kind;
    std::string m_name;

    std::unordered_set<Node*> m_neighbor[RELATION_COUNT];

    size_t print(char* a_buffer, size_t a_cnt) const noexcept;
};

} // namespace onto
