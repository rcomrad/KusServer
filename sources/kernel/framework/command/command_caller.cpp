#include "command_caller.hpp"

//------------------------------------------------------------------------------

#include "kernel/framework/core/kernel.hpp"
#include "kernel/framework/logger/include_me.hpp"

//------------------------------------------------------------------------------

core::CommandCaller::CommandCaller() : m_next_caller_num(0)
{
}

core::CommandCaller::~CommandCaller()
{
}

void
core::CommandCaller::registrateBaseCommand(const char* a_name,
                                           const char* a_description,
                                           const char* a_args)
{
    KERNEL.registrateCommand(m_next_caller_num++, a_name, this, a_description,
                             a_args);
}

//------------------------------------------------------------------------------

#define COMMAND_CALLER_IMPL(num)                                   \
    void core::CommandCaller::commandCall##num(Command& a_command) \
    {                                                              \
        THROW("Command executor #{} is not implemented.", #num);   \
    }

COMMAND_CALLER_IMPL(0);
COMMAND_CALLER_IMPL(1);
COMMAND_CALLER_IMPL(2);
COMMAND_CALLER_IMPL(3);
COMMAND_CALLER_IMPL(4);

#undef COMMAND_CALLER_IMPL

//------------------------------------------------------------------------------
