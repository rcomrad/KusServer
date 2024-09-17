#include "type.hpp"

#include "function.hpp"
#include "variable.hpp"

onto::Type::Type(const Command& a_command) noexcept
    : Node(Node::Kind::TYPE, a_command.m_name)
{
}

onto::Type::Type(const std::string_view& a_name) noexcept
    : Node(Node::Kind::TYPE, a_name)
{
}

void
onto::Type::returns(Function& a_func) noexcept
{
    a_func.addNeighbor(*this, Relation::RETURNS);
}

void
onto::Type::has_type(Variable& a_var) noexcept
{
    a_var.addNeighbor(*this, Relation::HAS_TYPE);
}
