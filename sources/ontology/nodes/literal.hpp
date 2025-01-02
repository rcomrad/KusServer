#pragma once

#include <optional>
#include <string>

#include "node.hpp"

namespace onto
{

struct Literal : public Node
{
    Literal(const std::string_view& a_name) noexcept;
};

} // namespace onto
