#include "program_state.hpp"

#include <sstream>
#include <utility>

#include "domain/file_reader.hpp"

core::ProgramState core::ProgramState::mThis;

core::ProgramState::ProgramState()
    : mRestartState(Restart::NUN),
      mAutoCheckAnswers(false),
      mSetTimeForAnswers(false),
      mTesterThreadCount(0)
{
    reloadSettings();
    if (mRestartOnStart == "full")
    {
        fullReset();
    }
    else if (mRestartOnStart == "empty")
    {
        emptyReset();
    }
    else if (mRestartOnStart == "tester")
    {
        testerReset();
    }
    // reloadSubmitionsQueue();
}

void
core::ProgramState::reloadSettings() noexcept
{
    auto settings = dom::FileReader::getAllStrings("main_settings.config");
    for (auto& i : settings)
    {
        std::stringstream ss;
        ss << i;
        std::string s;
        ss >> s;

        if (s == "tester_thread_count")
        {
            ss >> s;
            mTesterThreadCount = std::stoi(s);
        }
        else if (s == "restart_on_start")
        {
            ss >> mRestartOnStart;
        }
    }
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

void
core::ProgramState::testerReset()
{
    mRestartMutex.lock();
    mRestartState = Restart::TESTER;
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
}

bool
core::ProgramState::needRemakeDB()
{
    return mRestartState == Restart::FULL || mRestartState == Restart::EMPTY;
}

bool
core::ProgramState::needReloadSubmitions()
{
    return mRestartState == Restart::FULL || mRestartState == Restart::TESTER;
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

void
core::ProgramState::pushSubmition(
    data::Table<data::Submission>&& aSubmition) noexcept
{
    mSubmitionMutex.lock();
    mSubmitionsQueue.push(std::move(aSubmition));
    mSubmitionMutex.unlock();
}

data::Table<data::Submission>
core::ProgramState::getSubmition() noexcept
{
    const std::lock_guard<std::mutex> lock(mSetTimeMutex);
    data::Table<data::Submission> temp = std::move(mSubmitionsQueue.front());
    mSubmitionsQueue.pop();
    return std::move(temp);
}

bool
core::ProgramState::hasSubmition() noexcept
{
    const std::lock_guard<std::mutex> lock(mSetTimeMutex);
    return !mSubmitionsQueue.empty();
}

int
core::ProgramState::getTesterThreadCount() noexcept
{
    return mTesterThreadCount;
}

// void
// core::ProgramState::checkSubmitionsQueue() noexcept
// {
//     mSubmitionMutex.lock();
//     decltype(mSubmitionsQueue) empty;
//     std::swap(mSubmitionsQueue, empty);
//     if (mRestartState != Restart::EMPTY) reloadSubmitionsQueue();
//     mSubmitionMutex.unlock();
// }

void
core::ProgramState::reloadSubmitionsQueue() noexcept
{
    mSubmitionMutex.lock();
    decltype(mSubmitionsQueue) empty;
    std::swap(mSubmitionsQueue, empty);
    data::DatabaseQuery dbq(data::DatabaseQuery::UserType::USER);
    auto problemTable = dbq.getData<data::Submission>("verdict=\'NUN\'");
    for (auto& i : problemTable)
    {
        data::Table<data::Submission> sub;
        sub.emplace_back(std::move(i));
    }
    mSubmitionMutex.unlock();
}
