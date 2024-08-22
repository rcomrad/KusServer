#pragma once

//--------------------------------------------------------------------------------

#include <unordered_map>

#include "string/kus_string.hpp"

#include "callback_storage.hpp"
#include "command_register.hpp"
#include "holy_trinity.hpp"
#include "variable_storage.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class Module : public CommandRegister
{
public:
    Module(const char* a_name) noexcept;
    virtual ~Module() = default;

    void trigger_initialization() noexcept;
    virtual void initialize() noexcept;
    virtual void run() noexcept;
    virtual void terminate() noexcept;

    int getVatiable(int a_variable_num) noexcept;

protected:
    virtual void variableSetup(VariableInfoArray& a_set_array) noexcept;
    virtual void commandSetup() noexcept;

private:
    const char* m_name;
    int m_variable_offset;

    void loadVariables() noexcept;
};

} // namespace core

//--------------------------------------------------------------------------------
