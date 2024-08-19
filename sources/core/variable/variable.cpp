#include "variable.hpp"

core::Variable::Variable() noexcept : value(0), parser(nullptr)
{
}

core::Variable::Variable(std::string&& a_name,
                         FPVariableParser a_parser,
                         std::vector<std::string>&& a_possable_values) noexcept
    : name(std::move(a_name)),
      possable_values(std::move(a_possable_values)),
      value(0),
      parser(a_parser)
{
}

core::Variable::Variable(const Variable& other) noexcept
{
    name            = other.name;
    possable_values = other.possable_values;
    value           = int(other.value);
    parser          = other.parser;
}
