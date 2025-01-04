#pragma once

#include <string_view>

#include "node.hpp"

namespace onto
{

struct Operator : public Node
{
    Operator(const std::string_view& a_name) noexcept;
    Operator(const std::string_view& a_name,
             const std::vector<std::string_view>& a_parts);
};

} // namespace onto
