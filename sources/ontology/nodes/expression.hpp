#pragma once

#include <string_view>
#include <vector>

#include "node.hpp"

namespace onto
{

class Expression : public Node
{
public:
    Expression(const std::string_view& a_name,
               const std::vector<Node*>& a_parts);
    Expression(const std::string_view& a_name,
               const std::vector<std::string_view>& a_parts);

private:
    void addVariable(Node& a_var);
    void addLiteral(Node& a_var);
};

} // namespace onto
