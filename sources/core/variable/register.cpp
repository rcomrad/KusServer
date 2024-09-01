#include "register.hpp"

#include "storage.hpp"

int
core::VariableRegister::registerVariable(const char* a_var_name,
                                         const char** a_values,
                                         int a_value_count) noexcept
{
    return VariableStorage::addVariableInfo(a_var_name, a_values,
                                            a_value_count);
}

int
core::VariableRegister::registerVariable(
    VariableInfoArray&& a_var_data_array) noexcept
{
    int result = -1;
    for (auto&& i : a_var_data_array)
    {
        int temp = registerVariable(i.var_name, i.values, i.value_count);
        if (result == -1)
        {
            result = temp;
        }
    }
    return result;
}
