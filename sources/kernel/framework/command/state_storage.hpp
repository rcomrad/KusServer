#pragma once

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>

#include "kernel/framework/command/command_data.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class StateStorage
{
public:
    enum StateType
    {
        MERGE_ARGS = 1,
        RESET_ARGS = 2,
        MERGE_VARS = 4,
        RESET_VARS = 8
    };

    StateStorage();

    void listenCommand(const std::string& a_comm, int a_type);
    void storeCommand(const CommandData& a_command);
    void applyCommands();

private:
    struct CommandDataExt : public CommandData
    {
        CommandDataExt(const std::string& a_comm_str, int a_type)
            : CommandData(std::string(a_comm_str)), type(a_type)
        {
        }
        int type;
    };

    std::unordered_map<std::string, CommandDataExt> m_storage;

    void dumpState();
};
} // namespace core

//--------------------------------------------------------------------------------
