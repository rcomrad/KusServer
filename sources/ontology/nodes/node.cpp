#include "node.hpp"

// #include "web.hpp"

onto::Node::Node(onto::Node::Kind a_kind,
                 const std::string_view& a_name) noexcept
    : m_kind(a_kind), m_name(a_name)
{
}

onto::Node::Kind
onto::Node::getKind() const noexcept
{
    return m_kind;
}

const std::string&
onto::Node::getName() const noexcept
{
    return m_name;
}

void
onto::Node::addNeighbor(Node& a_node, Relation a_relation) noexcept
{
    m_neighbor[static_cast<int>(a_relation)].insert(&a_node);
    a_node.m_neighbor[getOpposite(a_relation)].insert(this);
}
