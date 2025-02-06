#pragma once

//--------------------------------------------------------------------------------

#include <array>
#include <string>
#include <map>
#include <unordered_set>
#include <vector>

#include "command.hpp"
#include "command_caller.hpp"
#include "input_buffer.hpp"

//--------------------------------------------------------------------------------

namespace core
{

class CommandHandler : public CommandCaller
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
    void execIfAvailable() const;
    void processCommand(Command& a_command) const;

private:
    mutable std::mutex m_buffers_mutex;
    std::unordered_set<InputBuffer*> m_inp_buffers;
    struct CommandInfo
    {
        int caller_num;
        CommandCaller* obj;
        const char* desc;
        const char* args;
    };
    std::map<std::string, CommandInfo> m_command_info;

    std::vector<std::string> sliceHelpDescription() const;

    COMMAND_HANDLER(help, 0);
    COMMAND_HANDLER(test, 1);
};

} // namespace core

//--------------------------------------------------------------------------------
