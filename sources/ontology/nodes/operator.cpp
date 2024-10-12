#include "operator.hpp"

onto::Operator::Operator(const std::string_view& a_name) noexcept
    : Node(Node::Kind::OPERATOR, a_name)
{
}
