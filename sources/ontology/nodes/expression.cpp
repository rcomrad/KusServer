#include "expression.hpp"

onto::Expression::Expression(const std::string_view& a_name) noexcept
    : Node(Node::Kind::EXPRESSION, a_name)
{
}
