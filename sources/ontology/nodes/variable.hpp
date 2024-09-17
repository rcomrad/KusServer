#pragma once

#include <optional>
#include <string>

#include "../command.hpp"

#include "node.hpp"

namespace onto
{

class Function;

struct Variable : public Node
{
    Variable(const Command& a_command) noexcept;
    Variable(const std::string_view& a_dump) noexcept;

    void is_argument(Function& a_func) noexcept;

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
