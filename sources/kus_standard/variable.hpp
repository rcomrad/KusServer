#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <string>
#include <unordered_map>

#include "value.hpp"

namespace str
{

struct Variable
{
    str::String name;
    Value value;
};

using VariableArray = std::unordered_map<str::String, Value>;

} // namespace str

#endif // !VARIABLE_HPP
