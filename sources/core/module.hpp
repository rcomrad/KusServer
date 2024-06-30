#pragma once

//--------------------------------------------------------------------------------

#include <unordered_map>

#include "string/kus_string.hpp"

#include "holy_trinity.hpp"
#include "variable_storage.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class Module
{
public:
    Module(const char* a_name) noexcept;
    virtual ~Module() = default;

    virtual void initialize() noexcept;
    virtual void run() noexcept;
    virtual void terminate() noexcept;
    virtual void variableSetup(VariableInfoArray& a_set_array) noexcept;

    int getVatiable(int a_variable_num) noexcept;

protected:
    void registerVariables() noexcept;

private:
    const char* m_name;
    int m_variable_offset;
};

} // namespace core

//--------------------------------------------------------------------------------
