#include "variable_cell.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"
#include "kernel/utility/string/conversion.hpp"
#include "kernel/utility/string/normalize.hpp"

//--------------------------------------------------------------------------------

core::VariableCell::VariableCell(const std::string& a_var_name)
    : m_name(a_var_name),
      m_value(0),
      m_type(Type::ANY),
      m_min_value(INT32_MIN),
      m_max_value(INT32_MAX)
{
}

core::VariableCell::VariableCell(const std::string& a_var_name, bool dummy)
    : m_name(a_var_name), m_value(0), m_type(Type::BOOL)
{
}

core::VariableCell::VariableCell(const std::string& a_var_name,
                                 int a_min_value,
                                 int a_max_value)
    : m_name(a_var_name),
      m_value(0),
      m_type(Type::RANGE),
      m_min_value(a_min_value),
      m_max_value(a_max_value)
{
}

core::VariableCell::VariableCell(const std::string& a_var_name,
                                 const std::vector<std::string>& a_values)
    : m_name(a_var_name), m_value(0), m_type(Type::WORD)
{
    for (int i = 0; i < a_values.size(); ++i)
    {
        std::string key = a_values[i];
        util::Normalize::change(key, util::Normalize::Type::LOWER);
        m_value_map.emplace(std::move(key), i);
    }
}

core::VariableCell::VariableCell(const VariableCell& other)
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

void
core::VariableCell::setValue(bool a_new_value) noexcept
{
    m_value = a_new_value ? 1 : 0;
}

void
core::VariableCell::setValue(int a_new_value)
{
    if (a_new_value < m_min_value)
    {
        THROW("Failed to set value '%d' for '%s' variable. The value is too "
              "low, minimum value is '%d'.",
              a_new_value, m_name, m_min_value);
    }

    if (a_new_value > m_max_value)
    {
        THROW("Failed to set value '%d' for '%s' variable. The value is too "
              "large, maximum value is '%d'.",
              a_new_value, m_name, m_min_value);
    }

    m_value = a_new_value;
}

void
core::VariableCell::setValue(std::string_view a_new_value)
{
    switch (m_type)
    {
        case Type::ANY:
            setValue(util::Conversion::stoi(a_new_value));
            break;

        case Type::RANGE:
            setValue(util::Conversion::stoi(a_new_value));
            break;

        case Type::WORD:
            setWordValue(a_new_value);
            break;

        case Type::BOOL:
            setWordBool(a_new_value);
            break;
    }
}

void
core::VariableCell::setWordValue(std::string_view a_new_value)
{
    auto norm_val =
        util::Normalize::copy(a_new_value, util::Normalize::Type::LOWER);
    auto val_it = m_value_map.find(norm_val);
    if (val_it != m_value_map.end())
    {
        THROW("Failed to set value '%s' for '%s' variable: unknown value.",
              a_new_value, m_name, m_min_value);
    }
    m_value = val_it->second;
}

void
core::VariableCell::setWordBool(std::string_view a_new_value)
{
    auto norm_val =
        util::Normalize::copy(a_new_value, util::Normalize::Type::LOWER);
    if (norm_val == "true")
    {
        m_value = 1;
    }
    else if (norm_val == "false")
    {
        m_value = 0;
    }
    else
    {
        THROW("Failed to set value '%s' for '%s' variable: unknown value, only "
              "'true' or 'false' available.",
              a_new_value, m_name, m_min_value);
    }
}

//--------------------------------------------------------------------------------

int
core::VariableCell::getValue() const noexcept
{
    return m_value;
}

const std::string&
core::VariableCell::getName() const noexcept
{
    return m_name;
}

//--------------------------------------------------------------------------------

void
core::VariableCell::addValueInfo(std::string& result) const
{
    result += "\t'";
    result += m_name;
    result += "' = ";
    result += std::to_string(m_value);
    result += "\n";
}

void
core::VariableCell::addValueMap(std::string& result) const
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
            result += std::string("from ") + std::to_string(m_min_value) +
                      " to " + std::to_string(m_max_value);
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
