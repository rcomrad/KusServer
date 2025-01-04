#include "literal.hpp"

onto::Literal::Literal(const std::string_view& a_name) noexcept
    : Node(Node::Kind::LITERAL, std::string(a_name))
{
}

onto::Literal::Literal(const std::string_view& a_name,
                       const std::vector<std::string_view>& a_parts)
    : Node(Node::Kind::LITERAL, a_name)
{
}
