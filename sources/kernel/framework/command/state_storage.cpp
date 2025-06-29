#include "state_storage.hpp"

#include "kernel/framework/command/input_buffer.hpp"
#include "kernel/framework/core/kernel.hpp"
#include "kernel/framework/logger/basic/include_me.hpp"
#include "kernel/utility/file_system/file_read.hpp"
#include "kernel/utility/file_system/file_write.hpp"
#include "kernel/utility/file_system/path_values.hpp"
#include "kernel/utility/string/parser.hpp"

namespace
{

constexpr const char* STATE_FILE_NAME = "program_state.txt";

}

core::StateStorage::StateStorage()
{
    KERNEL.addFile(util::DATA_FOLDER_NAME, STATE_FILE_NAME);
    dumpState();
}

void
core::StateStorage::listenCommand(const std::string& a_comm, int a_type)
{
    if (m_storage.count(a_comm))
    {
        THROW("The %s command is already being listened", a_comm);
    }
    m_storage.emplace(a_comm, CommandDataExt(a_comm, a_type));
}
void
core::StateStorage::storeCommand(const CommandData& a_command)
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
core::StateStorage::applyCommands()
{
    auto data     = util::FileRead::read(STATE_FILE_NAME);
    auto commands = util::Parser::getLinesRef(data);

    for (auto& i : commands)
    {
        InputBuffer buffer;
        auto cmd_out = buffer.execCommand(std::string(i));
        printf("%s", cmd_out.get());
    }
}

void
core::StateStorage::dumpState()
{
    util::FileWrite state_file(STATE_FILE_NAME);
    state_file.write(m_storage);
}
