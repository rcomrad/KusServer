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

    auto restartState = VariableStorage::touchWord("restart_on_start");
    if (!restartState.empty())
    {
        std::thread temp(static_cast<std::string (*)(const std::string&,
                                                     const std::string&)>(
                             &mult::CommandHandler::process),
                         "restart", restartState);
        temp.join();
    }
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
    mApps["server"] = std::move(std::thread(&Core::serverThread, this));
    if (VariableStorage::touchFlag("submission_auto_check"))
        mApps["tester"] = std::move(std::thread(&Core::testerThread, this));

    auto& killCommand = VariableStorage::touchWord("kill");
    while (!mKillFlag)
    {
        ModuleBase::process();
        if (!killCommand.empty()) mKillFlag = true;
    }
}

//--------------------------------------------------------------------------------

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
