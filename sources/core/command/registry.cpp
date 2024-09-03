#include "registry.hpp"

#include <memory>

#include "core/callback/storage.hpp"
#include "core/module/state_storage.hpp"

#include "utility/string/slicer.hpp"

#include "definitions.hpp"
#include "input_stdin.hpp"

SINGLETON_DEFINITOR(core, CommandHandler);

core::CommandHandler::CommandHandler() noexcept : Module("command_handler")
{
}

void
core::CommandHandler::listenNonstatic(InputBuffer* a_buffer) noexcept
{
    m_inp_buffers.insert(a_buffer);
}

void
core::CommandHandler::unlistenNonstatic(InputBuffer* a_buffer) noexcept
{
    m_inp_buffers.erase(a_buffer);
}

void
core::CommandHandler::addCommandInfoNonstatic(const char* a_comm_name,
                                              const char* a_help_info,
                                              const char* a_help_args) noexcept
{
    m_command_info[a_comm_name] =
        std::array<const char*, 2>{a_help_info, a_help_args};
}

void
core::CommandHandler::initialize() noexcept
{
    // InputSTDIN::listen();
}

void
core::CommandHandler::terminate() noexcept
{
    // InputSTDIN::unlisten();
}

void
core::CommandHandler::processCommandNonstatic(CommandExtend& a_command) noexcept
{
    auto temp =
        CallbackStorage::get(CALLBACK_VOLUME_COMMAND_HANDLER, a_command.value);
    if (nullptr != temp)
    {
        LOG_INFO("Apply command '%s'", a_command.value);
        reinterpret_cast<FP_CommandHandler>(temp)(a_command);
        if (!a_command.execResultIsError())
        {
            StateStorage::process(&a_command);
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

// TODO: yield
bool
core::CommandHandler::loopBody() noexcept
{
    std::optional<CommandExtend*> cmd_opt;
    for (auto& cmd_buff : m_inp_buffers)
    {
        cmd_opt = cmd_buff->obtainCommand();
        if (cmd_opt.has_value())
        {
            break;
        }
    }
    if (!cmd_opt.has_value())
    {
        return true;
    }
    processCommandNonstatic(*cmd_opt.value());

    return true;
}

void
core::CommandHandler::commandSetup() const noexcept
{
    registerCommand("help", showHelp,
                    "Assign a value to the specified variable.", "");
}

std::vector<std::string>
core::CommandHandler::sliceHelpDescription() const noexcept
{
    std::vector<std::string> result;
    for (auto& i : m_command_info)
    {
        int buff_size               = strlen(i.second[0]) + 10;
        std::unique_ptr<char[]> buf = std::make_unique<char[]>(buff_size);

        // TODO: const a_from_str
        auto sentence = util::Slicer::safeProcess(
            const_cast<char*>(i.second[0]), buf.get(), ".");
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

std::string
core::CommandHandler::composeHelpInfo() const noexcept
{
    std::string result;
    auto descriptions = sliceHelpDescription();
    int cnt           = 0;
    for (auto& i : m_command_info)
    {
        int init_size = result.size();
        int buff_size = 100;

        result.resize(init_size + buff_size);
        int printed_count =
            snprintf(result.data() + init_size, buff_size, "  %4d) %15s | %s",
                     cnt + 1, i.first.data(), i.second[1]);
        result.resize(init_size + printed_count);

        result += descriptions[cnt++];
        result.push_back('\n');
    }
    result.shrink_to_fit();
    return result;
}

void
core::CommandHandler::showHelpNonstatic(core::CommandExtend& a_command) noexcept
{
    static std::string info = composeHelpInfo();
    PRINT_CMD_MSG(a_command, "\nKusSystem command list:\n%s", info);
}
