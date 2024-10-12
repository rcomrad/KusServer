#pragma once

#include <optional>
#include <string>

#include "node.hpp"

namespace onto
{

class Function;
class Variable;

struct Type : public Node
{
    Type(const std::string_view& a_dump) noexcept;

    void result_for(Function& a_func) noexcept;
    void produce_var(Variable& a_var) noexcept;
};

} // namespace onto
