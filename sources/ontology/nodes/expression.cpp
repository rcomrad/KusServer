#include "expression.hpp"

#include <stdexcept>
#include <string>

#include "literal.hpp"
#include "variable.hpp"

onto::Expression::Expression(const std::string_view& a_name,
                             const std::vector<Node*>& a_parts)
    : Node(Node::Kind::EXPRESSION, std::string(a_name))
{
    for (auto& i : a_parts)
    {
        auto& node = *i;
        switch (node.getKind())
        {
            case Node::Kind::VARIABLE:
                addVariable(node);
                break;
            case Node::Kind::LITERAL:
                addLiteral(node);
                break;

            default:
                throw std::runtime_error(
                    "Unexpected expression parts type with id '" +
                    std::to_string(int(node.getKind())) + "'");
                break;
        }
    }
}

onto::Expression::Expression(const std::string_view& a_name,
                             const std::vector<std::string_view>& a_parts)
    : Node(Node::Kind::EXPRESSION, a_name)
{
}

void
onto::Expression::addVariable(Node& a_var)
{
    auto& variable = dynamic_cast<Variable&>(a_var);
    auto& value    = variable.getValue();
    addNeighbor(value, Relation::CONSIST_OF);
}

void
onto::Expression::addLiteral(Node& a_var)
{
    addNeighbor(a_var, Relation::CONSIST_OF);
}
