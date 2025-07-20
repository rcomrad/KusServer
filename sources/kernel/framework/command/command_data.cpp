#include "command_data.hpp"

#include <algorithm>

#include "kernel/utility/string/slicer.hpp"
#include "kernel/utility/unique.hpp"

core::CommandData::CommandData(std::string&& a_comm_str) noexcept
{
    m_data    = std::move(a_comm_str);
    auto args = util::Slicer::copy(m_data, "; \n\t");
    if (args.empty()) return;

    // first word is a command and processed separately
    value = args[0];

    for (int i = 1; i < args.size(); ++i)
    {
        auto temp = util::Slicer::copy(args[i], "=");
        if (temp.size() == 1)
        {
            // TODO: set?
            arguments.emplace_back(temp[0]);
        }
        else
        {
            variables[std::string(temp[0])] = std::string(temp[1]);
        }
    }
}

std::string
core::CommandData::toString() const noexcept
{
    std::string result(value);

    for (auto& i : arguments)
    {
        result.push_back(' ');
        result += i;
    }

    for (auto& i : variables)
    {
        result.push_back(' ');
        result += i.first;
        result.push_back('=');
        result += i.second;
    }

    return result;
}

void
core::CommandData::addArgs(const CommandData& a_other)
{
    arguments = util::Unique::combine(arguments, a_other.arguments);
}

void
core::CommandData::resetArgs(const CommandData& a_other)
{
    arguments = a_other.arguments;
}

void
core::CommandData::addVars(const CommandData& a_other)
{
    // TODO: util::Unique::combine
    for (auto& [i, j] : a_other.variables)
    {
        variables[i] = j;
    }
}

void
core::CommandData::resetVars(const CommandData& a_other)
{
    variables = a_other.variables;
}

bool
core::CommandData::hasArg(std::string_view a_str)
{
    return std::find(arguments.begin(), arguments.end(), a_str) !=
           arguments.end();
}
