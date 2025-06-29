#pragma once

//--------------------------------------------------------------------------------

// #include <mutex>
#include <string>
// #include <string_view>
#include <unordered_map>

#include "kernel/framework/command/command_data.hpp"
// #include "kernel/utility/file_system/file_write.hpp"
// #include "kernel/utility/macroses/holy_trinity.hpp"

// #include "command_sets.hpp"

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
    void storeCommand(const CommandData& a_command_ptr);
    void applyCommands();

private:
    std::unordered_map<std::string, std::pair<int, CommandData>> m_storage;
};
} // namespace core

//--------------------------------------------------------------------------------
