#include "command.hpp"

std::string_view
onto::Command::getNodeName(const Command& a_command) noexcept
{
    return a_command.m_name;
}

const std::string_view&
onto::Command::getNodeName(const std::string_view& a_name) noexcept
{
    return a_name;
}
