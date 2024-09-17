#include "function.hpp"

#include "../web.hpp"

onto::Function::Function(const Command& a_command) noexcept
    : Node(Node::Kind::FUNCTION, a_command.m_name)
{
    // a_web
    // a_web.connect(a_command.)
    a_command.m_type.value().returns(*this);
}

onto::Function::Function(const std::string_view& a_name) noexcept
    : Node(Node::Kind::FUNCTION, a_name)
{
}
