#pragma once

//--------------------------------------------------------------------------------

#include <atomic>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "command_register.hpp"
#include "holy_trinity.hpp"

//--------------------------------------------------------------------------------
/*
                                Class contruct

*/
//--------------------------------------------------------------------------------

namespace core
{

typedef int (*FPIntGlobVarToInt)(const str::string&);

struct VariableInfo
{
    const char* name;
    FPIntGlobVarToInt func;
};
using VariableInfoArray = std::vector<VariableInfo>;

class VariableStorage : public CommandRegister
{
public:
    HOLY_TRINITY_SINGLETON(VariableStorage);

    SINGL_RET_METHOD(int,
                     addVariableInfo,
                     (const VariableInfoArray& aVarSettings));
    SINGL_VOID_METHOD(reloadValuesFromFile, ());

    SINGL_VOID_METHOD(set, (int aNumber, int aValue));
    SINGL_RET_METHOD(int, get, (int aNumber));

    static const int CORRUPTED_VALUE;

private:
    struct Variable
    {
        std::atomic<int> value   = 0;
        FPIntGlobVarToInt parser = nullptr;

        Variable() noexcept = default;
        Variable(const Variable& other) noexcept;
    };

    std::vector<Variable> m_variables;
    std::unordered_map<std::string_view, int> m_name_to_var_dict;

    VariableStorage() noexcept;
    COMMAND_HANDLER_NONSTATIC(setCommandHandler);
    COMMAND_HANDLER_NONSTATIC(showVarCommandHandler);
};

} // namespace core

//--------------------------------------------------------------------------------
