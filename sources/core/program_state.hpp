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

    static ProgramState& getInstance();

    void fullReset();
    void emptyReset();

    bool needRestart();
    bool needPopulateDB();
    bool needRemakeDB();

    void startRestart();
    void endRestart();

private:
    static ProgramState mThis;

    Restart mRestartState;
    mutable std::mutex mMutex;

    ProgramState();
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !PROGRAM_STATE_HPP
