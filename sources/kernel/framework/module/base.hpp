#pragma once

//--------------------------------------------------------------------------------

#include "kernel/framework/command/handler.hpp"
#include "kernel/framework/command/input_stdin.hpp"
#include "kernel/framework/variable/storage.hpp"
#include "kernel/utility/file_system/path_storage.hpp"
#include "kernel/utility/type/declaration/lifecycle_manager.hpp"

#include "callback_storage.hpp"
#include "registry.hpp"
#include "state_storage.hpp"

//--------------------------------------------------------------------------------

namespace core
{

class Base : public VariableStorage,
             public CommandHandler,
             public CallbackStorage,
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
