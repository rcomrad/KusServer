#include "module_handler.hpp"

//--------------------------------------------------------------------------------

mod::ModuleHandler&
mod::ModuleHandler::getInstance() noexcept
{
    static ModuleHandler instance;
    return instance;
}

//--------------------------------------------------------------------------------

void
mod::ModuleHandler::run() noexcept
{
    getInstance().runNonstatic();
}

str::String
mod::ModuleHandler::processCommand(const char* aCommand,
                                   const char* aArgument) noexcept
{
    return getInstance().processCommandNonstatic(aCommand, aArgument);
}

//--------------------------------------------------------------------------------

void
mod::ModuleHandler::addCommand(const char* aCommand, ModuleBase* aPtr) noexcept
{
    getInstance().mModules[aCommand] = aPtr;
}

bool
mod::ModuleHandler::hasCommand(const char* aCommand) noexcept
{
    return getInstance().mModules.count(aCommand);
}

//--------------------------------------------------------------------------------

void
mod::ModuleHandler::executeCommand(int aResultNumber,
                                   const ModuleBase::Command& aCommand) noexcept
{
    auto it = mModules.find(aCommand.value);
    if (it != mModules.end())
    {
        auto res = it->second->doAction(aCommand);
        mResultMutex.lock();
        mResults[aResultNumber] = std::move(res);
        mResultMutex.unlock();
    }
}

void
mod::ModuleHandler::runNonstatic() noexcept
{
    mCommandMutex.lock();
    if (!mCommands.empty())
    {
        auto com = std::move(mCommands.back());
        mCommands.pop_back();
        mCommandMutex.unlock();

        executeCommand(com.num, com);
    }
    else
    {
        mCommandMutex.unlock();
    }
}

str::String
mod::ModuleHandler::processCommandNonstatic(const char* aCommand,
                                            const char* aArgument) noexcept
{
    str::String result;

    static int intglobalTesultCounter = 0;

    mCommandMutex.lock();
    ++intglobalTesultCounter;
    int curResultNum = intglobalTesultCounter;
    mCommands.emplace_back(curResultNum, aCommand, aArgument);
    mCommandMutex.unlock();

    bool flag = true;
    while (flag)
    {
        mResultMutex.lock();
        auto it = mResults.find(curResultNum);
        if (it != mResults.end())
        {
            result = std::move(it->second);
            mResults.erase(it);
            flag = false;
        }
        mResultMutex.unlock();
    }

    return result;
}
