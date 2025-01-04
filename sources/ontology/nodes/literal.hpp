#pragma once

#include <string_view>

#include "node.hpp"

namespace onto
{

struct Literal : public Node
{
    Literal(const std::string_view& a_name) noexcept;
    Literal(const std::string_view& a_name,
            const std::vector<std::string_view>& a_parts);
};

} // namespace onto
