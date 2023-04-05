#ifndef PROGRAM_STATE_HPP
#define PROGRAM_STATE_HPP

//--------------------------------------------------------------------------------

#include <mutex>
#include <queue>
#include <unordered_map>

#include "database/database_structures.hpp"

//--------------------------------------------------------------------------------

namespace core
{
enum class RestartType
{
    NUN,
    FULL,
    EMPTY,
    TESTER,
    SETTINGS
};

enum class Flag
{
    SUB_CHECK,
    ANS_CHECK,
    TIME_SET
};

enum class Value
{
    TEST_THRD,
    DB_THRD
};

class ProgramState
{
public:
    static ProgramState& getInstance();

    void callRestart(const RestartType& aType);
    void startRestart();
    void endRestart();

    bool needRestart();
    bool needPopulateDB();
    bool needRemakeDB();
    bool needReloadSubmitions();

    bool checkFlag(const Flag& aFlag) noexcept;
    int getValue(const Value& aName) noexcept;

private:
    ProgramState();
    void reloadSettings() noexcept;

    RestartType mStartState;
    RestartType mRestartState;
    mutable std::mutex mRestartMutex;

    std::unordered_map<std::string, RestartType> mRestartTypes;

    std::vector<uint8_t> mFlags;
    uint8_t turnOnOff(const std::string& s) noexcept;
    std::unordered_map<std::string, uint8_t&> mFlagNames;

    std::vector<int> mValues;
    int valueSetter(const std::string& s) noexcept;
    std::unordered_map<std::string, int&> mValueNames;
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !PROGRAM_STATE_HPP
