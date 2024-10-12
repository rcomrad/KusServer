#pragma once

#include <optional>
#include <string>

#include "node.hpp"

namespace onto
{

struct Operator : public Node
{
    Operator(const std::string_view& a_name) noexcept;
};

} // namespace onto
