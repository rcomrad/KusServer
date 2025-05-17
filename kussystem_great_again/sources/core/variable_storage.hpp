#pragma once

//--------------------------------------------------------------------------------

#include <atomic>
#include <unordered_map>
#include <vector>

#include "kus_standard/hash_map_by_str.hpp"

#include "callback_register.hpp"
#include "command.hpp"
#include "holy_trinity.hpp"
#include "int_glob_var.hpp"

//--------------------------------------------------------------------------------
/*
                                Class contruct

*/
//--------------------------------------------------------------------------------

namespace core
{

struct VarSetting
{
    const char* name;
    FPIntGlobVarToInt fptr;
};

class VariableStorage
{
public:
    HOLY_TRINITY_SINGLE(VariableStorage);

    static int addSettings(
        const std::vector<VarSetting>& aVarSettings) noexcept;
    static void reloadSettings() noexcept;

    static void set(int aNumber, int aValue) noexcept;
    static int get(int aNumber) noexcept;

    static const int CORRUPTED_VALUE;

private:
    static CallbackRegister mCommandHandlerCallback;

    std::vector<IntGlobVar> mVariables;
    HAS_MAP_BY_STR(mVariableNames, Variables, 200, int);

    VariableStorage() noexcept;
    static VariableStorage& getInstance() noexcept;

    int addSettingsNonstatic(
        const std::vector<VarSetting>& aVarSettings) noexcept;
    void reloadSettingsNonstatic() noexcept;

    void setNonstatic(int aNumber, int aValue) noexcept;
    int getNonstatic(int aNumber) noexcept;

    static void setCommandHandler(const Command& aCommand) noexcept;
    void setCommandHandlerNonstatic(const Command& aCommand) noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------
