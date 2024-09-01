#pragma once

//--------------------------------------------------------------------------------

#include <unordered_map>

#include "core/command/register.hpp"
#include "core/variable/register.hpp"
#include "core/variable/storage.hpp"

#include "string/kus_string.hpp"

#include "utility/common/holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class Module : public CommandRegister, private VariableRegister
{
public:
    Module(const char* a_name) noexcept;
    virtual ~Module() = default;

    void init() noexcept;
    void term() noexcept;
    void run() noexcept;

protected:
    virtual void initialize() noexcept;
    virtual void terminate() noexcept;
    virtual bool loopBody() noexcept;

    virtual void commandSetup() const noexcept;
    virtual void variableSetup() const noexcept;

    void setVariable(int a_variable_num, int a_variable_value) const noexcept;
    int getVariable(int a_variable_num) const noexcept;

    void registerVariable(const char* a_var_name,
                          const char** a_values,
                          int a_value_count) const noexcept;
    void registerVariable(VariableInfoArray&& a_var_data_array) const noexcept;

private:
    const char* m_name;
    mutable int m_variable_offset;

    void loadVariables() noexcept;
};

} // namespace core

//------------------------------------------------------------------------------
