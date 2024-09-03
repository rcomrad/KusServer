#include "state_storage.hpp"

#include <stdio.h>

#include "core/command/input_buffer.hpp"

#include "utility/file_system/file.hpp"
#include "utility/file_system/path.hpp"
#include "utility/file_system/path_storage.hpp"
#include "utility/file_system/path_values.hpp"
#include "utility/string/parser.hpp"

SINGLETON_DEFINITOR(core, StateStorage);

core::StateStorage::StateStorage() noexcept
{
    DECLARE_LOCAL_CONTEXT;
    util::PathStorage::addFile(util::DATA_FOLDER_NAME, util::COMMAND_FILE_NAME,
                               &context_local);
}

void
core::StateStorage::processNonstatic(const CommandData* a_command_ptr) noexcept
{
    const CommandData& command = *a_command_ptr;

    std::lock_guard<std::mutex> lock(m_storage_mutex);
    // TODO: string_view map
    auto it = m_command_types.find(std::string(command.value));
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
core::StateStorage::setStateTypeNonstatic(const std::string& a_comm,
                                          StateType a_type) noexcept
{
    std::lock_guard<std::mutex> lock(m_storage_mutex);
    m_command_types[a_comm] = a_type;
}

void
core::StateStorage::dumpState() noexcept
{
    FILE_WRITER(dumped, util::COMMAND_FILE_NAME);
    dumpContainer(dumped, m_base_commands);
    dumpContainer(dumped, m_argument_commands);
    dumpContainer(dumped, m_variable_commands);
    dumpContainer(dumped, m_unique_commands);
}

void
core::StateStorage::applyNonstatic() noexcept
{
    auto data = util::File::readStored(util::COMMAND_FILE_NAME);

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
                    util::COMMAND_FILE_NAME, util::DATA_FOLDER_NAME);
    }

    dumpState();
}
