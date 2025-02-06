#pragma once

//--------------------------------------------------------------------------------

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

//--------------------------------------------------------------------------------

namespace core
{
struct CommandData
{
    // TODO: consider string_view again
    std::string value;
    std::vector<std::string> arguments;
    std::unordered_map<std::string, std::string> variables;

    CommandData(std::string&& a_comm_str) noexcept;

private:
    // TODO: remove?
    std::string m_data; // real (unparsed) command string
};
} // namespace core

//--------------------------------------------------------------------------------
