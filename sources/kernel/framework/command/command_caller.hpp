#pragma once

//------------------------------------------------------------------------------

#include "command.hpp"

//------------------------------------------------------------------------------

namespace core
{

class Command;

#define COMMAND_CALLER(num) virtual void commandCall##num(Command& a_command);

class CommandCaller
{
public:
    CommandCaller();
    virtual ~CommandCaller();
    void exec_command(Command& a_command);

    COMMAND_CALLER(0);
    COMMAND_CALLER(1);
    COMMAND_CALLER(2);
    COMMAND_CALLER(3);
    COMMAND_CALLER(4);

protected:
    void registrateBaseCommand(const char* a_name,
                               const char* a_description,
                               const char* a_args);

private:
    int m_next_caller_num;
};

#undef COMMAND_CALLER

} // namespace core

// TODO: check to validity? a_command.str == command_name

#define COMMAND_HANDLER(command_name, num)                 \
    void command_name(Command& a_command);                 \
    inline void commandCall##num(Command& a_command) final \
    {                                                      \
        command_name(a_command);                           \
    }

#define COMMAND_HANDLER_CONST(command_name, num)           \
    void command_name(Command& a_command) const;           \
    inline void commandCall##num(Command& a_command) final \
    {                                                      \
        command_name(a_command);                           \
    }

//------------------------------------------------------------------------------
