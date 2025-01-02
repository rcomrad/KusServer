#pragma once

#include <optional>
#include <string>

#include "expression.hpp"
#include "node.hpp"
#include "type.hpp"

namespace onto
{

class Function;

class Variable : public Node
{
public:
    Variable(const std::string_view& a_dump, Type& a_type) noexcept;

    // void is_argument(Function& a_func) noexcept;

    void setValue(Expression& a_expr);
    Expression& getValue();

private:
    Expression* m_value;
};

} // namespace onto
