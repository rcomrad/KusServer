#include "core.hpp"

#include "code/generate_code.hpp"
#include "core/variable_storage.hpp"
#include "file_data/file.hpp"
#include "file_data/path.hpp"
#include "module/module_handler.hpp"
#include "multitool/command_handler.hpp"
#include "post/journal_handler.hpp"
#include "post/plan_handler.hpp"
#include "post/user_handler.hpp"
#include "server/server.hpp"
#include "tester/tester.hpp"

#include "role.hpp"
#include "submission_queue.hpp"
#include "variable_storage.hpp"

//--------------------------------------------------------------------------------

core::Core::Core() noexcept  :
    mAppIsTurnedOn  (true)
//: ModuleBase({"kill"}), mKillFlag(false)
{

    // code::CodeGenerator cg;
    // cg.makeAll();
    // cg.generate();

    // core::Role::getInstance();

    // file::Path::addContentFrom(file::Path::getPathUnsafe("resource"),
    //                            file::Path::FileType::File,
    //                            file::Path::LevelType::Recursive);
    // file::Path::addContentFrom(file::Path::getPathUnsafe("scripts"));
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
    start();
    while (!mKillFlag)
    {
        mod::ModuleHandler::run();
    }
    // start();
    // while (!mKillFlag)
    // {
    //     mod::ModuleHandler::run();
    // }
}

void
core::Core::setup() noexcept
{
    getInstance().run();
}

void
core::Core::runNonstatic() noexcept
{
    getInstance().run();
}

// str::string
// core::Core::doAction(const Command& aCommand) noexcept
// {
//     str::string res;

//     if (aCommand.value == "kill")
//     {
//         res       = "You're monster!";
//         mKillFlag = true;
//     }

//     return res;
// }

//--------------------------------------------------------------------------------

void
core::Core::start() noexcept
{
    mApps["server"] = std::move(std::thread(&Core::serverThread, this));
    if (VariableStorage::touchFlag("submission_auto_check"))
        mApps["tester"] = std::move(std::thread(&Core::testerThread, this));

    auto restartState = VariableStorage::touchWord("restart_on_start");
    if (restartState != "nun")
    {
        mApps["restart"] =
            std::move(std::thread(static_cast<str::string (*)(
                                      const str::string&, const str::string&)>(
                                      &mult::CommandHandler::process),
                                  "restart", restartState));
        // temp.join();
    }
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
