#pragma once

//--------------------------------------------------------------------------------

#include <mutex>
#include <string>
#include <string_view>
#include <unordered_map>

#include "kernel/framework/command/command_data.hpp"
#include "kernel/utility/defines/holy_trinity.hpp"
#include "kernel/utility/file_system/file_write.hpp"

#include "command_sets.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class StateStorage
{
public:
    enum class StateType
    {
        COMMAND,
        COMMAND_ARGS,
        COMMAND_VARS,
        UNIQUE
    };

    StateStorage();

    void stateProcess(const CommandData* a_command_ptr);
    void setStateType(const std::string& a_comm, StateType a_type);
    void apply();

private:
    std::mutex m_storage_mutex;

    CommandBaseSet m_base_commands;
    CommandArgSet m_argument_commands;
    CommandWarsSet m_variable_commands;
    CommandUniqSet m_unique_commands;

    std::unordered_map<std::string, StateType> m_command_types;

    void dumpState();
    template <typename C>
    void dumpContainer(util::FileWrite& a_file, const C& a_container)
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
