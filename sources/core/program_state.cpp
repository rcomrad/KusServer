#include "program_state.hpp"

#include <utility>

#include "database/connection_manager.hpp"

#include "file/file.hpp"

//--------------------------------------------------------------------------------

core::ProgramState::ProgramState()
    : mStartState(RestartType::NUN), mRestartState(RestartType::NUN)
{

    mFlags  = {0, 0, 1, 1};
    mValues = {1, 2};
    mWords  = {""};

    mRestartTypes = {
        {"full",   RestartType::FULL  },
        {"empty",  RestartType::EMPTY },
        {"tester", RestartType::TESTER}
    };

    mFlagNames = {
        {"submission_auto_check", mFlags[int(Flag::SUB_CHECK)]    },
        {"answers_auto_check",    mFlags[int(Flag::ANS_CHECK)]    },
        {"set_time_for_answer",   mFlags[int(Flag::TIME_SET)]     },
        {"authorisation",         mFlags[int(Flag::Authorisation)]}
    };

    mValueNames = {
        {"tester_thread_count",       mValues[int(Value::TEST_THRD)]},
        {"database_connection_count", mValues[int(Value::DB_THRD)]  }
    };

    mWordsNames = {
        {"default_path", mWords[int(Word::DEF_PATH)]}
    };

    reloadSettings();
    mRestartState = mStartState;
}

core::ProgramState&
core::ProgramState::getInstance()
{
    static ProgramState instance;
    return instance;
}

void
core::ProgramState::reloadSettings() noexcept
{
    auto settings = file::File::getWords("main_settings.conf");
    for (auto& i : settings)
    {
        std::string &name = i[0], &state = i[1];

        if (name == "restart_on_start")
        {
            auto it = mRestartTypes.find(state);
            if (it != mRestartTypes.end())
            {
                mStartState = it->second;
            }
            continue;
        }

        auto it1 = mFlagNames.find(name);
        if (it1 != mFlagNames.end())
        {
            it1->second = turnOnOff(state);
            continue;
        }

        auto it2 = mValueNames.find(name);
        if (it2 != mValueNames.end())
        {
            it2->second = valueSetter(state);
            continue;
        }

        auto it3 = mWordsNames.find(name);
        if (it3 != mWordsNames.end())
        {
            it3->second = state;
        }
    }
}

//--------------------------------------------------------------------------------

void
core::ProgramState::callRestart(const RestartType& aType)
{
    mRestartMutex.lock();
    mRestartState = aType;
    mRestartMutex.unlock();
}

void
core::ProgramState::startRestart()
{
    mRestartMutex.lock();
}

void
core::ProgramState::endRestart()
{
    if (mRestartState == RestartType::SETTINGS) reloadSettings();
    mRestartState = RestartType::NUN;
    mRestartMutex.unlock();
}

//--------------------------------------------------------------------------------

bool
core::ProgramState::needRestart()
{
    const std::lock_guard<std::mutex> lock(mRestartMutex);
    return mRestartState != RestartType::NUN;
}

bool
core::ProgramState::needPopulateDB()
{
    return mRestartState == RestartType::FULL;
}

bool
core::ProgramState::needRemakeDB()
{
    return mRestartState == RestartType::FULL ||
           mRestartState == RestartType::EMPTY;
}

bool
core::ProgramState::needReloadSubmitions()
{
    return mRestartState == RestartType::FULL ||
           mRestartState == RestartType::TESTER;
}

//--------------------------------------------------------------------------------

bool
core::ProgramState::checkFlag(const Flag& aFlag) noexcept
{
    // TODO: is it effective?
    // const std::lock_guard<std::mutex> lock(mRestartMutex);
    return mFlags[int(aFlag)];
}

int
core::ProgramState::getValue(const Value& aName) noexcept
{
    // TODO: is it effective?
    // const std::lock_guard<std::mutex> lock(mRestartMutex);
    return mValues[int(aName)];
}

std::string
core::ProgramState::getWord(const Word& aName) noexcept
{
    return mWords[int(aName)];
}

//--------------------------------------------------------------------------------

uint8_t
core::ProgramState::turnOnOff(const std::string& s) noexcept
{
    uint8_t result = 0;
    if (s == "on") result = 1;
    return result;
}

int
core::ProgramState::valueSetter(const std::string& s) noexcept
{
    return std::stoi(s);
}
