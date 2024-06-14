#pragma once

//--------------------------------------------------------------------------------

#include <atomic>
#include <unordered_map>
#include <vector>

#include "string/kus_string.hpp"

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

using VariableSettings = std::unordered_map<str::String, FPIntGlobVarToInt>;

class VariableStorage
{
public:
    HOLY_TRINITY_SINGLE(VariableStorage);

    static int addSettings(const VariableSettings& aVarSettings) noexcept;
    static void reloadSettings() noexcept;

    static void set(int aNumber, int aValue) noexcept;
    static int get(int aNumber) noexcept;

    static const int CORRUPTED_VALUE;

private:
    static CallbackRegister mCommandHandlerCallback;

    std::vector<IntGlobVar> mVariables;
    std::unordered_map<str::String, int> mVariableNames;

    VariableStorage() noexcept;
    static VariableStorage& getInstance() noexcept;

    int addSettingsNonstatic(const VariableSettings& aVarSet) noexcept;
    void reloadSettingsNonstatic() noexcept;

    void setNonstatic(int aNumber, int aValue) noexcept;
    int getNonstatic(int aNumber) noexcept;

    static void setCommandHandler(const Command& aCommand) noexcept;
    void setCommandHandlerNonstatic(const Command& aCommand) noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------
