#pragma once

//--------------------------------------------------------------------------------

#include <atomic>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

//--------------------------------------------------------------------------------

namespace core
{

struct VariableCell
{
public:
    explicit VariableCell(const std::string& a_var_name);
    VariableCell(const std::string& a_var_name, bool dummy);
    VariableCell(const std::string& a_var_name,
                 int a_min_value,
                 int a_max_value);
    VariableCell(const std::string& a_var_name,
                 const std::vector<std::string>& a_values);
    VariableCell(const VariableCell& other);

    void setValue(bool a_new_value) noexcept;
    void setValue(int a_new_value);
    void setValue(std::string_view a_new_value);
    void setValue(const VariableCell& a_new_value);
    int getValue() const noexcept;

    const std::string& getName() const noexcept;

    void addValueInfo(std::string& result) const;
    void addValueMap(std::string& result) const;

private:
    enum class Type
    {
        ANY,
        RANGE,
        WORD,
        BOOL
    };

    void setWordValue(std::string_view a_new_value);
    void setWordBool(std::string_view a_new_value);

    Type m_type;
    std::string m_name;
    int m_min_value;
    int m_max_value;
    std::unordered_map<std::string, int> m_value_map;
    std::atomic<int> m_value;
};

} // namespace core

//--------------------------------------------------------------------------------
