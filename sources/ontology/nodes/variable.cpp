#include "variable.hpp"

#include "function.hpp"

onto::Variable::Variable(const Command& a_command) noexcept
    : Node(Node::Kind::VARIABLE, a_command.m_name)
{
}

onto::Variable::Variable(const std::string_view& a_name) noexcept
    : Node(Node::Kind::VARIABLE, a_name)
{
}

void
onto::Variable::is_argument(Function& a_func) noexcept
{
    a_func.addNeighbor(*this, Relation::ARGUMENT_FOR);
}
