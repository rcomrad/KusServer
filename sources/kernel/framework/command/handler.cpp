#include "handler.hpp"

//--------------------------------------------------------------------------------

#include <memory>

#include "kernel/framework/logging/include_me.hpp"
#include "kernel/framework/module/callback_storage.hpp"
#include "kernel/framework/module/kernel.hpp"
#include "kernel/framework/module/state_storage.hpp"
#include "kernel/utility/common/exception.hpp"
#include "kernel/utility/string/slicer.hpp"

//--------------------------------------------------------------------------------

core::CommandHandler::CommandHandler()
{
}

void
core::CommandHandler::init()
{
    registrateBaseCommand("help", "Displays a list of all available commands.",
                          "");
    registrateBaseCommand(
        "___internal_test",
        "This command is used in unit tests. Don't use it. It's meaningless.",
        "");
}

//--------------------------------------------------------------------------------

std::mutex&
core::CommandHandler::listenCommandBuffer(InputBuffer* a_buffer)
{
    const std::lock_guard lock(m_buffers_mutex);
    m_inp_buffers.insert(a_buffer);
    return m_buffers_mutex;
}

void
core::CommandHandler::unlistenCommandBuffer(InputBuffer* a_buffer)
{
    m_inp_buffers.erase(a_buffer);
}

//--------------------------------------------------------------------------------

void
core::CommandHandler::registrateCommand(int a_caller_num,
                                        const char* a_name,
                                        CommandCaller* a_obj,
                                        const char* a_description,
                                        const char* a_args)
{
    m_command_info[a_name] = {a_caller_num, a_obj, a_description, a_args};
}

void
core::CommandHandler::execIfAvailable() const
{
    std::optional<Command*> cmd_opt;

    std::unique_lock lock(m_buffers_mutex);
    for (auto& cmd_buff : m_inp_buffers)
    {
        cmd_opt = cmd_buff->obtainCommand();
        if (cmd_opt.has_value())
        {
            break;
        }
    }
    lock.unlock();

    if (!cmd_opt.has_value())
    {
        return;
    }
    processCommand(*cmd_opt.value());
}

#define CALL_CASE(num)                             \
    case num:                                      \
        com_info.obj->commandCall##num(a_command); \
        break;

void
core::CommandHandler::processCommand(Command& a_command) const
{
    auto it = m_command_info.find(a_command.value);
    if (it != m_command_info.end())
    {
        LOG_INFO("Apply command '%s'", a_command.value);

        auto& com_info = it->second;
        switch (com_info.caller_num)
        {
            CALL_CASE(0);
            CALL_CASE(1);
            CALL_CASE(2);
            CALL_CASE(3);
            CALL_CASE(4);

            default:
                THROW("There are no command executor with #{}.",
                      com_info.caller_num);
                break;
        }

        if (!a_command.execResultIsError())
        {
            KERNEL.stateProcess(&a_command);
        }
        LOG_INFO("      command '%s' was applied", a_command.value);
    }
    else
    {
        PRINT_CMD_ERR(
            a_command,
            "Unable to apply command '%s'. No suitable command handler",
            a_command.value);
    }

    a_command.callResultFunc();
}

#undef CALL_CASE

//--------------------------------------------------------------------------------
// Help command
//--------------------------------------------------------------------------------

// TODO: rewrite

void
core::CommandHandler::help(core::Command& a_command)
{
    std::string info;
    auto descriptions = sliceHelpDescription();
    int cnt           = 0;
    for (const auto& i : m_command_info)
    {
        if (i.first == "___internal_test")
        {
            continue;
        }

        int init_size = info.size();
        int buff_size = 100;

        info.resize(init_size + buff_size);
        int printed_count =
            snprintf(info.data() + init_size, buff_size, "  %4d) %15s | %s",
                     cnt + 1, i.first.data(), i.second.args);
        info.resize(init_size + printed_count);

        info += descriptions[cnt++];
        info.push_back('\n');
    }
    info.shrink_to_fit();
    PRINT_CMD_MSG(a_command, "\nKusSystem command list:\n%s", info);
}

std::vector<std::string>
core::CommandHandler::sliceHelpDescription() const
{
    std::vector<std::string> result;
    for (const auto& i : m_command_info)
    {
        int buff_size               = strlen(i.second.desc) + 100;
        std::unique_ptr<char[]> buf = std::make_unique<char[]>(buff_size);

        // TODO: const a_from_str
        auto sentence = util::Slicer::safeProcess(
            const_cast<char*>(i.second.desc), buf.get(), ".");
        for (int i = 1; i < sentence.size(); ++i)
        {
            sentence[i] = std::string_view(sentence[i].data() + 1,
                                           sentence[i].size() - 1);
        }

        int tab_size = 24;
        buff_size += sentence.size() * 10 + tab_size;
        result.emplace_back();
        result.back().resize(buff_size, 0);
        int actual_size = 0;
        for (auto& j : sentence)
        {
            actual_size += snprintf(result.back().data() + actual_size,
                                    buff_size - actual_size, "\n%*s|\t%s.",
                                    tab_size, "", j.data());
        }
        result.back().resize(actual_size);
        result.back().push_back('\n');
    }
    return result;
}

//--------------------------------------------------------------------------------
// Test command
//--------------------------------------------------------------------------------

void
core::CommandHandler::test(core::Command& a_command)
{
    PRINT_CMD_MSG(a_command, "Test successful!");
}

//--------------------------------------------------------------------------------
