#include "variable.hpp"

#include "function.hpp"

onto::Variable::Variable(const std::string_view& a_name, Type& a_type) noexcept
    : Node(Node::Kind::VARIABLE, a_name)
{
    addNeighbor(a_type, Relation::HAS_TYPE);
}

// void
// onto::Variable::is_argument(Function& a_func) noexcept
// {
//     a_func.addNeighbor(*this, Relation::ARGUMENT_FOR);
// }

void
onto::Variable::setValue(Expression& a_expr)
{
    m_value = &a_expr;
    clearRelationIfExist(Relation::STORES);
    addNeighbor(a_expr, Relation::STORES);
}

onto::Expression&
onto::Variable::getValue()
{
    return *m_value;
}
