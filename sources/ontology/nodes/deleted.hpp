#pragma once

#include "node.hpp"

namespace onto
{

struct Deleted : public Node
{
    Deleted(const std::string_view& a_name);
    Deleted(const std::string_view& a_name,
            const std::vector<std::string_view>& a_parts);
};

} // namespace onto
