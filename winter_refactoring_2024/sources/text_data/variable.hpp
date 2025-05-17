#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <string>
#include <unordered_map>

#include "value.hpp"

namespace text
{

struct Variable
{
    std::string name;
    Value value;
};

using VariableArray = std::unordered_map<std::string, Value>;

} // namespace file

#endif // !VARIABLE_HPP
