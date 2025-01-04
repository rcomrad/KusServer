#include "variable.hpp"

#include "function.hpp"

onto::Variable::Variable(const std::string_view& a_name, Type& a_type) noexcept
    : Node(Node::Kind::VARIABLE, a_name)
{
    addNeighbor(a_type, Relation::HAS_TYPE);
}

onto::Variable::Variable(const std::string_view& a_name,
                         const std::vector<std::string_view>& a_parts)
    : Node(Node::Kind::VARIABLE, a_name)
{
}

// void
// onto::Variable::is_argument(Function& a_func) noexcept
// {
//     a_func.addNeighbor(*this, Relation::ARGUMENT_FOR);
// }

void
onto::Variable::setValue(Expression& a_expr)
{
    setValue(dynamic_cast<Node&>(a_expr));
}

void
onto::Variable::setValue(UserData& a_data)
{
    setValue(dynamic_cast<Node&>(a_data));
}

void
onto::Variable::setValue(Node& a_node)
{
    m_value = &a_node;
    clearRelationIfExist(Relation::STORES);
    addNeighbor(a_node, Relation::STORES);
}

onto::Node&
onto::Variable::getValue()
{
    return *m_value;
}
