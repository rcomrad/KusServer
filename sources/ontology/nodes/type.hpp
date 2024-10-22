#pragma once

#include <optional>
#include <string>

#include "../command.hpp"

#include "node.hpp"

namespace onto
{

class Function;
class Variable;

struct Type : public Node
{
    Type(const Command& a_command) noexcept;
    Type(const std::string_view& a_dump) noexcept;

    void result_for(Function& a_func) noexcept;
    void produce_var(Variable& a_var) noexcept;

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
