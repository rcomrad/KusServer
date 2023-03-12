#include "program_state.hpp"

core::ProgramState core::ProgramState::mThis;

core::ProgramState::ProgramState()
    : mRestartState(Restart::NUN), mAutoCheckAnswers(false),
      mSetTimeForAnswers(false)
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
    mRestartMutex.lock();
    mRestartState = Restart::FULL;
    mRestartMutex.unlock();
}

void
core::ProgramState::emptyReset()
{
    mRestartMutex.lock();
    mRestartState = Restart::EMPTY;
    mRestartMutex.unlock();
}

// void
// core::ProgramState::repopulateReset()
// {
//     const std::lock_guard<std::mutex> lock(mRestartMutex);
//     mRestartState = Restart::POPULATE;
// }

bool
core::ProgramState::needRestart()
{
    const std::lock_guard<std::mutex> lock(mRestartMutex);
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
    mRestartMutex.lock();
}

void
core::ProgramState::endRestart()
{
    mRestartState = Restart::NUN;
    mRestartMutex.unlock();
}

void
core::ProgramState::setCheckAnswers(core::ProgramState::State aTurn)
{
    const std::lock_guard<std::mutex> lock(mCheckMutex);
    mAutoCheckAnswers = aTurn == State::ON;
}

void
core::ProgramState::setSettingTime(core::ProgramState::State aTurn)
{
    const std::lock_guard<std::mutex> lock(mSetTimeMutex);
    mSetTimeForAnswers = aTurn == State::ON;
}

bool
core::ProgramState::isCheckAnswersTurnOn()
{
    const std::lock_guard<std::mutex> lock(mCheckMutex);
    return mAutoCheckAnswers;
}

bool
core::ProgramState::isSetTimeTurnOn()
{
    const std::lock_guard<std::mutex> lock(mSetTimeMutex);
    return mSetTimeForAnswers;
}
