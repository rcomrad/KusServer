#pragma once

#include <string_view>

#include "expression.hpp"
#include "node.hpp"
#include "type.hpp"
#include "user_data.hpp"

namespace onto
{

class Function;

class Variable : public Node
{
public:
    Variable(const std::string_view& a_dump, Type& a_type) noexcept;
    Variable(const std::string_view& a_name,
             const std::vector<std::string_view>& a_parts);
    // void is_argument(Function& a_func) noexcept;

    void setValue(Expression& a_expr);
    void setValue(UserData& a_data);
    Node& getValue();

private:
    Node* m_value;

    void setValue(Node& a_node);
};

} // namespace onto
