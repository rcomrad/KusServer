#ifndef PROGRAM_STATE_HPP
#define PROGRAM_STATE_HPP

//--------------------------------------------------------------------------------

#include <mutex>

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
        EMPTY
        // ,
        // POPULATE
    };

    enum class State
    {
        NUN,
        ON,
        OFF
    };

    static ProgramState& getInstance();

    void fullReset();
    void emptyReset();

    bool needRestart();
    bool needPopulateDB();
    bool needRemakeDB();

    void startRestart();
    void endRestart();

    void setCheckAnswers(State aTurn);
    void setSettingTime(State aTurn);

    bool isCheckAnswersTurnOn();
    bool isSetTimeTurnOn();

private:
    static ProgramState mThis;

    Restart mRestartState;
    mutable std::mutex mRestartMutex;
    mutable std::mutex mCheckMutex;
    mutable std::mutex mSetTimeMutex;

    bool mAutoCheckAnswers;
    bool mSetTimeForAnswers;

    ProgramState();
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !PROGRAM_STATE_HPP
