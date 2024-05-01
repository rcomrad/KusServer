#pragma once

//--------------------------------------------------------------------------------

#include <atomic>
#include <string>
#include <unordered_map>

#include "domain/holy_trinity.hpp"
#include "domain/metaprogramming.hpp"

//--------------------------------------------------------------------------------
/*
                                Class contruct

*/
//--------------------------------------------------------------------------------

namespace core
{
typedef bool (*FPVariableToInt)(char);

class VariableStorage
{
public:
    HOLY_TRINITY_SINGLE(VariableStorage);

    static int addSettings(std::vector<FPVariableToInt> aParserFPs) noexcept;
    static void reloadSettings() noexcept;

    static void set(int aNumber, int aValue) noexcept;
    static int get(int aNumber) noexcept;

private:
    struct Variable
    {
        std::atomic<int> mValue;
        FPVariableToInt mParser;
    };

    std::vector<Variable> mVariables;

    VariableStorage() noexcept;
    static VariableStorage& getInstance() noexcept;

    int addSettingsNonstatic(std::vector<FPVariableToInt> aParserFPs) noexcept;
    void reloadSettingsNonstatic() noexcept;

    void setNonstatic(int aNumber, int aValue) noexcept;
    int getNonstatic(int aNumber) noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------
