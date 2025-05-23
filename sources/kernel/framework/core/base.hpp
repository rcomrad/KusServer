#pragma once

//--------------------------------------------------------------------------------

#include "kernel/framework/command/handler.hpp"
#include "kernel/framework/command/input_stdin.hpp"
#include "kernel/framework/module/registry.hpp"
#include "kernel/framework/state/state_storage.hpp"
#include "kernel/framework/variable/storage.hpp"
#include "kernel/utility/file_system/path_storage.hpp"
#include "kernel/utility/type/declaration/lifecycle_manager.hpp"

//--------------------------------------------------------------------------------

namespace core
{

class Base : public VariableStorage,
             public CommandHandler,
             public util::PathStorage,
             public StateStorage,
             public ModuleRegistry
{
public:
    Base();
    ~Base();

    void run();
    void runWhileDoesSmth();
    bool isRunning() const;
    void stop();

    void listenSTDIN() noexcept;

private:
    size_t m_is_running_var_num;
    util::LifecycleManager<InputSTDIN> m_stdin;
};

} // namespace core

//--------------------------------------------------------------------------------
