#pragma once

#include <optional>
#include <string>

#include "../command.hpp"

#include "node.hpp"

namespace onto
{

struct Function : public Node
{
    Function(const Command& a_command) noexcept;
    Function(const std::string_view& a_name) noexcept;

    // std::string type;
    // Module module;

    // std::string action;
    // std::optional<std::string> functor;
    // bool has_subblock;
};

} // namespace onto
