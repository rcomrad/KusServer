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
    std::string_view value;
    std::vector<std::string_view> arguments;
    std::unordered_map<std::string_view, std::string_view> variables;

    CommandData(std::string&& a_comm_str) noexcept;

private:
    // real (unparsed) command string
    std::string m_data;
};
} // namespace core

//--------------------------------------------------------------------------------
