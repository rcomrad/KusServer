#include "literal.hpp"

onto::Literal::Literal(const std::string_view& a_name) noexcept
    : Node(Node::Kind::LITERAL, a_name)
{
}
