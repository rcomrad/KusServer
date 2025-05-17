#include "core.hpp"

#include "code/generate_code.hpp"

#include "domain/variable_storage.hpp"

#include "text_data/path.hpp"

#include "module/module_handler.hpp"

#include "server/server.hpp"

#include "tester/tester.hpp"

#include "general_tools/log.hpp"

#include "role.hpp"
#include "submission_queue.hpp"

//--------------------------------------------------------------------------------

route::RouterNode core::Core::mRouterNode("module",
                                          "kill",
                                          (void*)&core::Core::doAction);

//--------------------------------------------------------------------------------

core::Core::Core() noexcept : mKillFlag(false)
{
    code::CodeGenerator cg;
    cg.makeAll();
    cg.generate();

    core::Role::getInstance();

    text::Path::addContentFrom(text::Path::getPathUnsafe("resource"),
                               text::Path::FileType::File,
                               text::Path::LevelType::Recursive);
    text::Path::addContentFrom(text::Path::getPathUnsafe("scripts"));
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
    auto restartState =
        dom::VariableStorage::touchWord("restart_on_start", "nun");
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
core::Core::doAction(const route::Command& aCommand) noexcept
{
    return getInstance().doActionNonstatic(aCommand);
}

std::string
core::Core::doActionNonstatic(const route::Command& aCommand) noexcept
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
    if (dom::VariableStorage::touchFlag("submission_auto_check"))
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
            LOG_INFO("start_checking");
            test::Tester tester(
                dom::VariableStorage::touchInt("tester_thread_count"));
            tester.run(sub.get());
            LOG_INFO("end_checking");
        }
    }
}
