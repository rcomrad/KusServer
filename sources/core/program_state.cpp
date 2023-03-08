#include "program_state.hpp"

core::ProgramState core::ProgramState::mThis;

core::ProgramState::ProgramState() : mRestartState(Restart::NUN)
{
}

core::ProgramState&
core::ProgramState::getInstance()
{
    return mThis;
}

void
core::ProgramState::fullReset()
{
    mMutex.lock();
    mRestartState = Restart::FULL;
    mMutex.unlock();
}

void
core::ProgramState::emptyReset()
{
    mMutex.lock();
    mRestartState = Restart::EMPTY;
    mMutex.unlock();
}

// void
// core::ProgramState::repopulateReset()
// {
//     const std::lock_guard<std::mutex> lock(mMutex);
//     mRestartState = Restart::POPULATE;
// }

bool
core::ProgramState::needRestart()
{
    const std::lock_guard<std::mutex> lock(mMutex);
    return mRestartState != Restart::NUN;
}

bool
core::ProgramState::needPopulateDB()
{
    return mRestartState == Restart::FULL;
    // ||
    //        mRestartState == Restart::POPULATE;
}

bool
core::ProgramState::needRemakeDB()
{
    return mRestartState == Restart::FULL || mRestartState == Restart::EMPTY;
}

void
core::ProgramState::startRestart()
{
    mMutex.lock();
}

void
core::ProgramState::endRestart()
{
    mRestartState = Restart::NUN;
    mMutex.unlock();
}
