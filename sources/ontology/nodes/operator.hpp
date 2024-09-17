#pragma once

#include <optional>
#include <string>

#include "../command.hpp"

#include "node.hpp"

namespace onto
{

struct Operator : public Node
{
    Operator(const Command& a_command) noexcept;
    Operator(const std::string_view& a_name) noexcept;

    // enum Kind
    // {
    //     BASIC,
    //     CONTAINER
    // };
    // enum Owner
    // {
    //     STD,
    //     SELF
    // };
    // std::optional<Type*> subtype;
};

} // namespace onto
