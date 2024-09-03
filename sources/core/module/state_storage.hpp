#pragma once

//--------------------------------------------------------------------------------

#include <mutex>
#include <string>
#include <string_view>
#include <unordered_map>

#include "core/command/command_data.hpp"

#include "utility/common/holy_trinity.hpp"
#include "utility/file_system/file_write.hpp"

#include "command_sets.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class StateStorage
{
public:
    HOLY_TRINITY_SINGLETON(StateStorage);

    enum class StateType
    {
        COMMAND,
        COMMAND_ARGS,
        COMMAND_VARS,
        UNIQUE
    };

    SINGL_VOID_METHOD(process, (const CommandData* a_command_ptr));
    SINGL_VOID_METHOD(setStateType,
                      (const std::string& a_comm, StateType a_type));
    SINGL_VOID_METHOD(apply, ());

private:
    std::mutex m_storage_mutex;

    CommandBaseSet m_base_commands;
    CommandArgSet m_argument_commands;
    CommandWarsSet m_variable_commands;
    CommandUniqSet m_unique_commands;

    // TODO: string_view map
    std::unordered_map<std::string, StateType> m_command_types;

    StateStorage() noexcept;

    void dumpState() noexcept;
    template <typename C>
    void dumpContainer(util::FileWrite& a_file, const C& a_container) noexcept
    {
        for (auto& comm : a_container)
        {
            a_file.write("%s ", comm.value.data());
            for (auto& i : comm.arguments)
            {
                a_file.write("%s ", i.data());
            }
            for (auto& i : comm.variables)
            {
                a_file.write("%s=%s ", i.first.data(), i.second.data());
            }
            a_file.write("\n");
        }
    }

    template <typename T>
    static void update_container(T& a_container, std::string&& a_comm_str)
    {
        // TODO: remove copy
        std::string str_cpy = a_comm_str;
        CommandData command_data(std::move(str_cpy));
        auto it = a_container.find(command_data);
        if (it != a_container.end())
        {
            a_container.erase(it);
        }
        a_container.insert(std::move(a_comm_str));
    }
};
} // namespace core

//--------------------------------------------------------------------------------
