#pragma once

#include <optional>
#include <string>

#include "node.hpp"
#include "type.hpp"

namespace onto
{

struct Function : public Node
{
    Function(const std::string_view& a_name, Type& a_type) noexcept;
};

} // namespace onto
