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

std::string
onto::Node::print() const noexcept
{
    auto size = print(nullptr, 0);
    std::string result(size, '\0');
    print(result.data(), size);
    return result;
}

size_t
onto::Node::print(char* a_buffer, size_t a_cnt) const noexcept
{
    size_t base_ptr = reinterpret_cast<size_t>(a_buffer);
    a_buffer += snprintf(a_buffer, a_cnt, "%s\n", m_name.data());

    for (auto& neighbors : m_neighbor)
    {
        if (neighbors.empty()) continue;

        a_buffer += snprintf(a_buffer, a_cnt,
                             "\t%s:", getRelationName(&neighbors - m_neighbor));
        for (auto& nei_set : neighbors)
        {
            a_buffer +=
                snprintf(a_buffer, a_cnt, "\t\t%s", nei_set->getName().data());
        }
    }
    return reinterpret_cast<size_t>(a_buffer) - base_ptr;
}

bool
onto::Node::isLonelyNode() const noexcept
{
    int size = 0;
    for (const auto& i : m_neighbor)
    {
        size += i.size();
    }
    return size == 0;
}
