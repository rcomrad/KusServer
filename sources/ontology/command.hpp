#pragma once

#include <boost/optional/optional.hpp>

#include <optional>
#include <string>
#include <vector>

#include "nodes/node.hpp"

namespace onto
{

class Type;
class Function;
class Variable;
class Operator;

struct Command
{
    // bool has_subblock;
    // std::optional<std::string> type;
    // std::optional<std::string> name;
    // std::optional<std::string> action;
    // std::optional<std::string> functor;

    std::string m_name;
    boost::optional<Type&> m_type;
    boost::optional<Operator&> m_operator;
    std::vector<Variable*> m_arguments;

    static std::string_view getNodeName(const Command& a_command) noexcept;
    static const std::string_view& getNodeName(
        const std::string_view& a_name) noexcept;
};

} // namespace onto
