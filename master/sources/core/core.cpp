#include "core.hpp"

#include "code/generate_code.hpp"

#include "file_data/path.hpp"

#include "module/module_handler.hpp"

#include "server/server.hpp"

#include "tester/tester.hpp"

#include "role.hpp"
#include "submission_queue.hpp"
#include "variable_storage.hpp"

//--------------------------------------------------------------------------------

route::RouterNode core::Core::mRouterNode(
    "module", {"kill"}, []() { return (void*)&core::Core::doAction; });

//--------------------------------------------------------------------------------

core::Core::Core() noexcept : mKillFlag(false)
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
core::Core::setup() noexcept
{
    auto restartState = VariableStorage::touchWord("restart_on_start", "nun");
    if (restartState != "nun")
    {
        mod::ModuleHandler::applyCommand("restart", restartState);
    }
}

void
core::Core::run() noexcept
{
    start();
    while (!mKillFlag)
    {
        mod::ModuleHandler::run();
    }
}

//--------------------------------------------------------------------------------

std::string
core::Core::doAction(const modul::Command& aCommand) noexcept
{
    return getInstance().doActionNonstatic(aCommand);
}

std::string
core::Core::doActionNonstatic(const modul::Command& aCommand) noexcept
{
    std::string result;

    if (aCommand.value == "kill")
    {
        result    = "You're monster!";
        mKillFlag = true;
    }

    return result;
}

//--------------------------------------------------------------------------------

void
core::Core::start() noexcept
{
    mApps["server"] = std::move(std::thread(&Core::serverThread, this));
    if (VariableStorage::touchFlag("submission_auto_check"))
        mApps["tester"] = std::move(std::thread(&Core::testerThread, this));
}

void
core::Core::serverThread() noexcept
{
    // TODO: without thread
    serv::Server app;
    while (!mKillFlag) continue;
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
