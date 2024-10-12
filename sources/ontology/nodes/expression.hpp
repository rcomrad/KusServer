#pragma once

#include <optional>
#include <string>

#include "node.hpp"

namespace onto
{

struct Expression : public Node
{
    Expression(const std::string_view& a_name) noexcept;
};

} // namespace onto
