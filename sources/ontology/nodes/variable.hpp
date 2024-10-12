#pragma once

#include <optional>
#include <string>

#include "node.hpp"
#include "type.hpp"

namespace onto
{

class Function;

struct Variable : public Node
{
    Variable(const std::string_view& a_dump, Type& a_type) noexcept;

    void is_argument(Function& a_func) noexcept;
};

} // namespace onto
