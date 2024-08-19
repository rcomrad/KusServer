#include "register.hpp"

#include "storage.hpp"

int
core::VariableRegister::registerVariable(
    std::string&& a_var_name,
    FPVariableParser a_parse_func,
    std::vector<std::string>&& a_possable_values) noexcept
{
    return VariableStorage::addVariableInfo(std::move(a_var_name), a_parse_func,
                                            std::move(a_possable_values));
}

int
core::VariableRegister::registerVariable(
    VariableInfoArray&& a_var_data_array) noexcept
{
    int result = -1;
    for (auto&& i : a_var_data_array)
    {
        int temp = registerVariable(std::move(i.var_name), i.parse_func,
                                    std::move(i.possable_values));
        if (result == -1)
        {
            result = temp;
        }
    }
    return result;
}
