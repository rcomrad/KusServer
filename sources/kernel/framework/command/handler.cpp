#include "handler.hpp"

//--------------------------------------------------------------------------------

#include <memory>

#include "kernel/framework/core/kernel.hpp"
#include "kernel/framework/logger/include_me.hpp"
#include "kernel/utility/string/slicer.hpp"

#include "state_storage.hpp"

//--------------------------------------------------------------------------------

core::CommandHandler::CommandInfo::CommandInfo(int a_caller_num,
                                               CommandCaller* a_obj,
                                               const char* a_desc,
                                               const char* a_args)
    : caller_num(a_caller_num), obj(a_obj), desc(a_desc), args(a_args)
{
}

void
core::CommandHandler::CommandInfo::print() const
{
    auto& arg_cell =
        addCell(args).alignmentLeft().addPrefix("Args: ").setDefault(
            "/* no args */");
    addSubline();
    addCell(arg_cell, desc).alignmentLeft();
    addSubline();
    noHead();
}

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
    m_command_info.try_emplace(a_name, a_caller_num, a_obj, a_description,
                               a_args);
}

bool
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
        return false;
    }
    processCommand(*cmd_opt.value());
    return true;
}

#define CALL_CASE(num)                             \
    case num:                                      \
        com_info.obj->commandCall##num(a_command); \
        break;

void
core::CommandHandler::processCommand(Command& a_command) const
{
    TeeLogger tee(a_command.m_result_buffer);

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
            KERNEL.storeCommand(a_command);
            LOG_INFO("      command '%s' applied successfully",
                     a_command.value);
        }
    }
    else
    {
        LOG_ERROR("Unable to apply command '%s'. No suitable command handler",
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
    LOG_CMD("%s", buildTable().get());
}

void
core::CommandHandler::print() const
{
    getKeyInfo().alignmentRight().setSeparator('|');
    setDefaultSeparator(' ');
    addTableConrainer(m_command_info,
                      std::unordered_set<std::string>{"___internal_test"});
}

//--------------------------------------------------------------------------------
// Test command
//--------------------------------------------------------------------------------

void
core::CommandHandler::test(core::Command& a_command)
{
    LOG_CMD("Test successful!");
}

//--------------------------------------------------------------------------------
