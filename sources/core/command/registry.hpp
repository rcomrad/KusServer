#pragma once

//--------------------------------------------------------------------------------

#include <array>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "core/module/module.hpp"

#include "command_extend.hpp"
#include "input_buffer.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class CommandHandler : public Module
{
public:
    HOLY_TRINITY_SINGLETON(CommandHandler);
    CommandHandler() noexcept;

    SINGL_VOID_METHOD(listen, (InputBuffer * a_buffer));
    SINGL_VOID_METHOD(unlisten, (InputBuffer * a_buffer));

    SINGL_VOID_METHOD(addCommandInfo,
                      (const char* a_comm_name,
                       const char* a_help_info,
                       const char* a_help_args));

    SINGL_VOID_METHOD(processCommand, (CommandExtend & a_command));

protected:
    void initialize() noexcept override;
    void terminate() noexcept override;
    bool loopBody() noexcept override;

    void commandSetup() const noexcept override;

private:
    std::unordered_set<InputBuffer*> m_inp_buffers;
    std::unordered_map<std::string_view, std::array<const char*, 2>>
        m_command_info;

    std::vector<std::string> sliceHelpDescription() const noexcept;
    std::string composeHelpInfo() const noexcept;
    COMMAND_HANDLER_NONSTATIC(showHelp);
};

} // namespace core

//--------------------------------------------------------------------------------
