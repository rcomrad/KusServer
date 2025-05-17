#include "core.hpp"

#include "code/generate_code.hpp"
#include "core/variable_storage.hpp"
#include "file_data/file.hpp"
#include "file_data/path.hpp"
#include "multitool/command_handler.hpp"
#include "post/journal_handler.hpp"
#include "post/plan_handler.hpp"
#include "post/user_handler.hpp"
#include "server/server.hpp"
#include "tester/tester.hpp"

#include "module_base.hpp"
#include "populate.hpp"
#include "role.hpp"
#include "submission_queue.hpp"
#include "variable_storage.hpp"

//--------------------------------------------------------------------------------

core::Core::Core() noexcept
    : ModuleBase("core", file::Value::Type::String), mKillFlag(false)
{
    code::CodeGenerator cg;
    cg.makeAll();
    cg.generate();

    core::Role::getInstance();

    file::Path::addContentFrom(file::Path::getPathUnsafe("resource"),
                               file::Path::FileType::File,
                               file::Path::LevelType::Recursive);
    file::Path::addContentFrom(file::Path::getPathUnsafe("scripts"));
}

core::Core&
core::Core::getInstance() noexcept
{
    static Core instance;
    return instance;
}

//--------------------------------------------------------------------------------

void
core::Core::run() noexcept
{
    // core::VariableStorage::setVariable("core", "start", 0ms);
    start();

    while (!mKillFlag)
    {
        ModuleBase::process();
    }
}

std::string
core::Core::doAction() noexcept
{
    static auto& command = VariableStorage::touchWord("core");

    std::string res;
    if (command == "start")
    {
        start();
    }
    else if (command == "kill")
    {
        res       = "You're monster!";
        mKillFlag = true;
    }

    return res;
}

//--------------------------------------------------------------------------------

void
core::Core::start() noexcept
{
    mApps["server"] = std::move(std::thread(&Core::serverThread, this));
    if (VariableStorage::touchFlag("submission_auto_check"))
        mApps["tester"] = std::move(std::thread(&Core::testerThread, this));

    auto restartState = VariableStorage::touchWord("restart_on_start");
    if (!restartState.empty())
    {
        mApps["restart"] =
            std::move(std::thread(static_cast<std::string (*)(
                                      const std::string&, const std::string&)>(
                                      &mult::CommandHandler::process),
                                  "restart", restartState));
        // temp.join();
    }

    VariableStorage::setVariable("executed_command"s, ""s, 0ms);
    VariableStorage::setVariable("command_result"s, ""s, 0ms);
}

void
core::Core::serverThread() noexcept
{
    // TODO: without thread
    serv::Server app;
    while (true)
        ;
}

void
core::Core::testerThread() noexcept
{
    auto& sub = SubmissionQueue::getInstance();
    while (!mKillFlag)
    {
        if (!sub.isEmpty())
        {
            dom::writeInfo("start_checking");
            test::Tester tester(
                VariableStorage::touchInt("tester_thread_count"));
            tester.run(sub.get());
            dom::writeInfo("end_checking");
        }
    }
}
