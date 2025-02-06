#include "variable.hpp"

#include <format>

#include "kernel/utility/common/exception.hpp"
#include "kernel/utility/string/normalize.hpp"

//--------------------------------------------------------------------------------

core::Variable::Variable(const std::string& a_var_name)
    : m_name(a_var_name),
      m_value(0),
      m_type(Type::ANY),
      m_min_value(INT32_MIN),
      m_max_value(INT32_MAX)
{
}

core::Variable::Variable(const std::string& a_var_name, bool dummy)
    : m_name(a_var_name), m_value(0), m_type(Type::BOOL)
{
}

core::Variable::Variable(const std::string& a_var_name,
                         int a_min_value,
                         int a_max_value)
    : m_name(a_var_name),
      m_value(0),
      m_type(Type::RANGE),
      m_min_value(a_min_value),
      m_max_value(a_max_value)
{
}

core::Variable::Variable(const std::string& a_var_name,
                         const std::vector<std::string>& a_values)
    : m_name(a_var_name), m_value(0), m_type(Type::WORD)
{
    for (int i = 0; i < a_values.size(); ++i)
    {
        std::string key = a_values[i];
        util::Normalize::notation(key, util::Normalize::Type::LOWER);
        m_value_map.emplace(std::move(key), i);
    }
}

core::Variable::Variable(const Variable& other)
{
    m_name  = other.m_name;
    m_value = int(other.m_value);
    m_type  = other.m_type;

    switch (other.m_type)
    {
        case Type::RANGE:
            m_min_value = other.m_min_value;
            m_max_value = other.m_max_value;
            break;

        case Type::WORD:
            m_value_map = other.m_value_map;
            break;
    }
}

//--------------------------------------------------------------------------------

bool
core::Variable::setValue(bool a_new_value) noexcept
{
    m_value = a_new_value ? 1 : 0;
    return true;
}

bool
core::Variable::setValue(int a_new_value) noexcept
{
    bool result = false;
    if (a_new_value > m_min_value && a_new_value < m_max_value)
    {
        m_value = a_new_value;
        result  = true;
    }
    return result;
}

bool
core::Variable::setValue(const std::string& a_new_value)
{
    bool result;
    switch (m_type)
    {
        case Type::ANY:
            result = setValue(std::stoi(a_new_value));
            break;

        case Type::RANGE:
            result = setValue(std::stoi(a_new_value));
            break;

        case Type::WORD:
            result = setWordValue(a_new_value);
            break;

        case Type::BOOL:
            result = setWordBool(a_new_value);
            break;
    }
    return result;
}

bool
core::Variable::setWordValue(const std::string& a_new_value)
{
    bool result = false;
    auto norm_val =
        util::Normalize::notation(a_new_value, util::Normalize::Type::LOWER);
    auto val_it = m_value_map.find(norm_val);
    if (val_it != m_value_map.end())
    {
        m_value = val_it->second;
        result  = true;
    }
    return result;
}

bool
core::Variable::setWordBool(const std::string& a_new_value)
{
    bool result = false;
    auto norm_val =
        util::Normalize::notation(a_new_value, util::Normalize::Type::LOWER);
    if (norm_val == "true")
    {
        m_value = 1;
        result  = true;
    }
    else if (norm_val == "false")
    {
        m_value = 0;
        result  = true;
    }
    return result;
}

//--------------------------------------------------------------------------------

int
core::Variable::getValue() const noexcept
{
    return m_value;
}

const std::string&
core::Variable::getName() const noexcept
{
    return m_name;
}

//--------------------------------------------------------------------------------

void
core::Variable::addValueInfo(std::string& result) const
{
    result += "\t'";
    result += m_name;
    result += "' = ";
    result += std::to_string(m_value);
    result += "\n";
}

void
core::Variable::addValueMap(std::string& result) const
{
    result += "\t'";
    result += m_name;
    result += "' = ";

    switch (m_type)
    {
        case Type::ANY:
            result += "no value limitations";
            break;

        case Type::RANGE:
            result += std::format("from {} to {}", m_min_value, m_max_value);
            break;

        case Type::WORD:
            for (auto& j : m_value_map)
            {
                result += "'" + std::string(j.first) + "' | ";
            }
            break;

        case Type::BOOL:;
            result = m_value ? "true" : "false";
            break;
    }

    result.pop_back();
    result.back() = '\n';
}
