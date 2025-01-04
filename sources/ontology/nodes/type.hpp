#pragma once

#include <string_view>

#include "node.hpp"

namespace onto
{

// class Function;
// class Variable;

struct Type : public Node
{
    Type(const std::string_view& a_dump) noexcept;
    Type(const std::string_view& a_name,
         const std::vector<std::string_view>& a_parts);

    // void result_for(Function& a_func) noexcept;
    // void produce_var(Variable& a_var) noexcept;
};

} // namespace onto
