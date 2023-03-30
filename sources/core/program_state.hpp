#ifndef PROGRAM_STATE_HPP
#define PROGRAM_STATE_HPP

//--------------------------------------------------------------------------------

#include <mutex>
#include <queue>

#include "database/database_query.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class ProgramState
{
public:
    enum class Restart
    {
        NUN,
        FULL,
        EMPTY,
        TESTER
        // POPULATE
    };

    enum class State
    {
        NUN,
        ON,
        OFF
    };

    static ProgramState& getInstance();

    void reloadSettings() noexcept;

    void fullReset();
    void emptyReset();
    void testerReset();

    bool needRestart();
    bool needPopulateDB();
    bool needRemakeDB();
    bool needReloadSubmitions();

    void startRestart();
    void endRestart();

    void setCheckAnswers(State aTurn);
    void setSettingTime(State aTurn);

    bool isCheckAnswersTurnOn();
    bool isSetTimeTurnOn();

    void pushSubmition(data::Table<data::Submission>&& aSubmition) noexcept;
    data::Table<data::Submission> getSubmition() noexcept;
    bool hasSubmition() noexcept;

    int getTesterThreadCount() noexcept;

    // void checkSubmitionsQueue() noexcept;
    void reloadSubmitionsQueue() noexcept;

private:
    static ProgramState mThis;

    std::string mRestartOnStart;
    Restart mRestartState;
    mutable std::mutex mRestartMutex;
    mutable std::mutex mCheckMutex;
    mutable std::mutex mSetTimeMutex;

    bool mAutoCheckAnswers;
    bool mSetTimeForAnswers;

    int mTesterThreadCount;

    bool mSubmitionRestart;
    std::queue<data::Table<data::Submission>> mSubmitionsQueue;
    mutable std::mutex mSubmitionMutex;

    ProgramState();
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !PROGRAM_STATE_HPP
