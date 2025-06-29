#include "state_storage.hpp"

#include "kernel/framework/logger/basic/include_me.hpp"

// #include <stdio.h>

#include "kernel/framework/command/input_buffer.hpp"
// #include "kernel/framework/core/kernel.hpp"
// #include "kernel/utility/file_system/file.hpp"
// #include "kernel/utility/file_system/path.hpp"
// #include "kernel/utility/file_system/path_storage.hpp"
// #include "kernel/utility/file_system/path_values.hpp"
// #include "kernel/utility/string/parser.hpp"

namespace
{

constexpr const char* STATE_FILE_NAME = "program_state.txt";

}

core::StateStorage::StateStorage()
{
    KERNEL.addFile(util::DATA_FOLDER_NAME, STATE_FILE_NAME);
}

void
core::StateStorage::listenCommand(const std::string& a_comm, int a_type)
{
    if (m_storage.count(a_comm))
    {
        THROW("The %s command is already being listened", a_comm);
    }
    m_storage.emplace(a_comm, a_type, a_comm);
}
void
core::StateStorage::storeCommand(const CommandData& a_command_ptr)
{
    auto it = m_storage.find(command.value);
    if (it == m_command_types.end())
    {
        return;
    }
    auto type  = it->second.first;
    auto& data = it->second.second;

    if (type & MERGE_ARGS)
    {
        data.addArgs();
    }
    else if (type & RESET_ARGS)
    {
        data.resetArgs();
    }

    if (type & MERGE_VARS)
    {
        data.addVars();
    }
    else if (type & RESET_VARS)
    {
        data.resetVars();
    }

    dumpState();
}

void
core::StateStorage::setStateType(const std::string& a_comm, StateType a_type)
{
    std::lock_guard<std::mutex> lock(m_storage_mutex);
    m_command_types[a_comm] = a_type;
}

void
core::StateStorage::dumpState()
{
    util::FileWrite state_file(STATE_FILE_NAME);
    state_file.write(m_storage);
}

void
core::StateStorage::apply()
{
    auto data = util::File::readStored(COMMAND_FILE_NAME);

    if (data.has_value())
    {
        auto commands = util::Parser::getLines(data.value());

        for (auto&& i : commands)
        {
            InputBuffer buffer;
            auto cmd_out = buffer.execCommand(std::string(i));
            printf("%s", cmd_out.get());
        }
    }
    else
    {
        LOG_WARNING("Can't reach command file with name '%s' in '%s'.",
                    COMMAND_FILE_NAME, util::DATA_FOLDER_NAME);
    }

    dumpState();
}
