#pragma once

//--------------------------------------------------------------------------------

#include <array>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

#include "kernel/framework/logger/include_me.hpp"

#include "command.hpp"
#include "command_caller.hpp"
#include "input_buffer.hpp"

//--------------------------------------------------------------------------------

namespace core
{

class CommandHandler : public CommandCaller, protected TablePrinter
{
public:
    CommandHandler();

    std::mutex& listenCommandBuffer(InputBuffer* a_buffer);
    void unlistenCommandBuffer(InputBuffer* a_buffer);

    void registrateCommand(int a_caller_num,
                           const char* a_name,
                           CommandCaller* a_obj,
                           const char* a_description,
                           const char* a_args);

protected:
    void init();
    bool execIfAvailable() const;
    void processCommand(Command& a_command) const;

private:
    mutable std::mutex m_buffers_mutex;
    std::unordered_set<InputBuffer*> m_inp_buffers;
    struct CommandInfo : TablePrinter
    {
        CommandInfo(int a_caller_num,
                    CommandCaller* a_obj,
                    const char* a_desc,
                    const char* a_args);

        int caller_num;
        CommandCaller* obj;
        const char* desc;
        const char* args;

        void print() const final;
    };
    std::map<std::string, CommandInfo> m_command_info;

    COMMAND_HANDLER(help, 0);
    COMMAND_HANDLER(test, 1);

    void print() const final;
};

} // namespace core

//--------------------------------------------------------------------------------
