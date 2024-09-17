#include "operator.hpp"

onto::Operator::Operator(const Command& a_command) noexcept
    : Node(Node::Kind::OPERATOR, a_command.m_name)
{
}

onto::Operator::Operator(const std::string_view& a_name) noexcept
    : Node(Node::Kind::OPERATOR, a_name)
{
}
