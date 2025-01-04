#include "type.hpp"

// #include "function.hpp"
// #include "variable.hpp"

onto::Type::Type(const std::string_view& a_name) noexcept
    : Node(Node::Kind::TYPE, a_name)
{
}

onto::Type::Type(const std::string_view& a_name,
                 const std::vector<std::string_view>& a_parts)
    : Node(Node::Kind::TYPE, a_name)
{
}
// void
// onto::Type::result_for(Function& a_func) noexcept
// {
//     a_func.addNeighbor(*this, Relation::RETURNS);
// }

// void
// onto::Type::produce_var(Variable& a_var) noexcept
// {
//     a_var.addNeighbor(*this, Relation::HAS_TYPE);
// }
