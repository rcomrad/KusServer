#pragma once

#include <string_view>

#include "node.hpp"
#include "type.hpp"

namespace onto
{

struct Function : public Node
{
    Function(const std::string_view& a_name, Type& a_type) noexcept;
    Function(const std::string_view& a_name,
             const std::vector<std::string_view>& a_parts);
};

} // namespace onto
