#include "variable.hpp"

#include "function.hpp"

onto::Variable::Variable(const std::string_view& a_name, Type& a_type) noexcept
    : Node(Node::Kind::VARIABLE, a_name)
{
    addNeighbor(a_type, Relation::HAS_TYPE);
}

void
onto::Variable::is_argument(Function& a_func) noexcept
{
    a_func.addNeighbor(*this, Relation::ARGUMENT_FOR);
}
