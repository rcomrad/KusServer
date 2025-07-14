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

struct Variable
{
public:
    Variable(const std::string& a_var_name);
    Variable(const std::string& a_var_name, bool dummy);
    Variable(const std::string& a_var_name, int a_min_value, int a_max_value);
    Variable(const std::string& a_var_name,
             const std::vector<std::string>& a_values);
    Variable(const Variable& other);

    bool setValue(bool a_new_value) noexcept;
    bool setValue(int a_new_value) noexcept;
    bool setValue(const std::string& a_new_value);
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

    bool setWordValue(const std::string& a_new_value);
    bool setWordBool(const std::string& a_new_value);

    Type m_type;
    std::string m_name;
    int m_min_value;
    int m_max_value;
    std::unordered_map<std::string, int> m_value_map;
    std::atomic<int> m_value;
};

} // namespace core

//--------------------------------------------------------------------------------
