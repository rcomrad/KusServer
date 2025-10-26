#pragma once

//--------------------------------------------------------------------------------

#include "kernel/framework/core/kernel.hpp"

//--------------------------------------------------------------------------------

namespace core
{

template <typename T>
struct Variable
{
public:
    template <typename... Args>
    Variable(Args&&... args)
    {
        m_id = KERNEL.addVariableInfo(std::forward<Args>(args)...);
    }

    int get() const
    {
        return KERNEL.getVariable(m_id);
    }

    void setVariable(T a_value)
    {
        KERNEL.setVariable(m_id, a_value);
    }

private:
    int m_id;
};

} // namespace core

//--------------------------------------------------------------------------------
