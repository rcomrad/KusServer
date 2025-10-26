#include "state_storage.hpp"

#include "kernel/framework/command/input_buffer.hpp"
#include "kernel/framework/core/kernel.hpp"
#include "kernel/framework/logger/basic/include_me.hpp"
#include "kernel/utility/string/parser.hpp"

namespace core
{

bool StateStorage::m_state_restore_flag = true;
constexpr const char* STATE_PATH        = "state";
constexpr const char* STATE_FILE_NAME   = "program_state.txt";

StateStorage::StateStorage()
{
    KERNEL.addDataShortcut(STATE_PATH, std::filesystem::path(STATE_FILE_NAME));
}

void
StateStorage::listenCommand(const std::string& a_comm, int a_type)
{
    if (m_storage.count(a_comm))
    {
        THROW("The %s command is already being listened", a_comm);
    }
    m_storage.emplace(a_comm, CommandDataExt(a_comm, a_type));
}
void
StateStorage::storeCommand(const CommandData& a_command)
{
    auto it = m_storage.find(a_command.value);
    if (it == m_storage.end())
    {
        return;
    }
    auto type  = it->second.type;
    auto& data = static_cast<CommandData&>(it->second);

    if (type & MERGE_ARGS)
    {
        data.addArgs(a_command);
    }
    else if (type & RESET_ARGS)
    {
        data.resetArgs(a_command);
    }

    if (type & MERGE_VARS)
    {
        data.addVars(a_command);
    }
    else if (type & RESET_VARS)
    {
        data.resetVars(a_command);
    }

    dumpState();
}

void
StateStorage::applyCommands()
{
    if (!m_state_restore_flag) return;

    auto data     = KERNEL.readFile(STATE_PATH);
    auto commands = utils::Parser::getLinesRef(data);

    for (auto& i : commands)
    {
        InputBuffer buffer;
        auto cmd_out = buffer.execCommand(std::string(i));

        std::string temp(cmd_out.get());
        temp.pop_back(); // remove \n
        LOG_INFO("Command result: %s", temp);
    }
}

void
StateStorage::turnOffStateRestore()
{
    m_state_restore_flag = false;
}

void
StateStorage::dumpState()
{
    KERNEL.writeFile(m_storage, STATE_PATH);
}

} // namespace core
