#include "state_storage.hpp"

#include <stdio.h>

#include "kernel/framework/command/input_buffer.hpp"
#include "kernel/framework/core/kernel.hpp"
#include "kernel/utility/file_system/file.hpp"
#include "kernel/utility/file_system/path.hpp"
#include "kernel/utility/file_system/path_storage.hpp"
#include "kernel/utility/file_system/path_values.hpp"
#include "kernel/utility/string/parser.hpp"

namespace
{

constexpr const char* COMMAND_FILE_NAME = "command.txt";

}

core::StateStorage::StateStorage()
{
    KERNEL.addFile(util::DATA_FOLDER_NAME, COMMAND_FILE_NAME);
}

void
core::StateStorage::stateProcess(const CommandData* a_command_ptr)
{
    const CommandData& command = *a_command_ptr;
    std::lock_guard<std::mutex> lock(m_storage_mutex);

    auto it = m_command_types.find(command.value);
    if (it == m_command_types.end())
    {
        return;
    }

    std::string comm_str(command.value);
    comm_str.push_back(' ');
    for (auto& i : command.arguments)
    {
        comm_str += i;
        comm_str.push_back(' ');
    }
    for (auto& i : command.variables)
    {
        comm_str += i.first;
        comm_str.push_back('=');
        comm_str += i.second;
        comm_str.push_back(' ');
    }

    switch (it->second)
    {
        case StateType::COMMAND:
            update_container(m_base_commands, std::move(comm_str));
            break;
        case StateType::COMMAND_ARGS:
            update_container(m_argument_commands, std::move(comm_str));
            break;
        case StateType::COMMAND_VARS:
            update_container(m_variable_commands, std::move(comm_str));
            break;
        case StateType::UNIQUE:
            m_unique_commands.emplace_back(std::move(comm_str));
            break;
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
    util::FileWrite dumped(COMMAND_FILE_NAME);
    dumpContainer(dumped, m_base_commands);
    dumpContainer(dumped, m_argument_commands);
    dumpContainer(dumped, m_variable_commands);
    dumpContainer(dumped, m_unique_commands);
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
