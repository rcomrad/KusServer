#pragma once

//--------------------------------------------------------------------------------

#include <atomic>
#include <string>
#include <unordered_map>
#include <vector>

#include "domain/holy_trinity.hpp"
#include "domain/metaprogramming.hpp"
#include "domain/pair.hpp"

#include "string/kus_string.hpp"

//--------------------------------------------------------------------------------
/*
                                Class contruct

*/
//--------------------------------------------------------------------------------

namespace core
{

typedef int (*FPVariableToInt)(const str::string&);
using VariableSettings = std::unordered_map<str::string, FPVariableToInt>;

class VariableStorage
{
public:
    HOLY_TRINITY_SINGLE(VariableStorage);

    static int addSettings(const VariableSettings& aVarSettings) noexcept;
    static void reloadSettings() noexcept;

    static void set(int aNumber, int aValue) noexcept;
    static int get(int aNumber) noexcept;

private:
    struct Variable
    {
        // HOLY_TRINITY_NOCOPY(Variable);
        Variable(int aValue, FPVariableToInt aParser) noexcept;
        Variable(Variable&& other) noexcept;
        Variable& operator=(Variable&& other) noexcept;

        std::atomic<int> mValue = 0;
        FPVariableToInt mParser = nullptr;
    };

    std::vector<Variable> mVariables;
    std::unordered_map<std::string, int> mVariableNames;

    VariableStorage() noexcept;
    static VariableStorage& getInstance() noexcept;

    int addSettingsNonstatic(const VariableSettings& aVarSet) noexcept;
    void reloadSettingsNonstatic() noexcept;

    void setNonstatic(int aNumber, int aValue) noexcept;
    int getNonstatic(int aNumber) noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------
