#include "command_sets.hpp"

bool
core::CommandSets::BaseComparator::operator()(
    const CommandData& first,
    const CommandData& second) const noexcept
{
    return first.value < second.value;
}

bool
core::CommandSets::ArgsComparator::operator()(
    const CommandData& first,
    const CommandData& second) const noexcept
{
    return commandCompare(first, second, first.arguments, second.arguments);
}

bool
core::CommandSets::VarsComparator::operator()(
    const CommandData& first,
    const CommandData& second) const noexcept
{
    return commandCompare(first, second, first.variables, second.variables);
}
