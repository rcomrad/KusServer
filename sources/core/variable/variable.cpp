#include "variable.hpp"

#include "utility/string/normalize.hpp"

core::Variable::Variable() noexcept : value(0)
{
}

core::Variable::Variable(const char* a_var_name,
                         const char** a_values,
                         int a_value_count) noexcept
    : name(a_var_name), value(0)
{
    value_array.reserve(a_value_count);
    for (int i = 0; i < a_value_count; ++i)
    {
        value_array.emplace_back(a_values[i]);
        util::Normalize::notation(value_array.back(),
                                  util::Normalize::Type::LOWER);
        value_map[value_array.back()] = i;
    }
}

core::Variable::Variable(const Variable& other) noexcept
{
    name      = other.name;
    value_map = other.value_map;
    value     = int(other.value);
}
