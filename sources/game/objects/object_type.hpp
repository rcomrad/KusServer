#pragma once

#include <string>
#include <unordered_set>

namespace game::obj
{

enum class Type
{
    COORDINATABLE = 1,
    DRAWABLE      = 2,
    HITABLE       = 4,
    TEXTABLE      = 8
};

int
generateTypeMask(const std::unordered_set<std::string>& a_type_flags);

} // namespace game::obj
