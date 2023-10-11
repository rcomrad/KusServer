#ifndef VARIABLE_STORAGE_HPP
#define VARIABLE_STORAGE_HPP

//--------------------------------------------------------------------------------

#include <boost/optional.hpp>

#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>

#include "domain/holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class VariableStorage
{
public:
    HOLY_TRINITY_SINGLE(VariableStorage);

    static bool isLocked() noexcept;
    static void beginLock(
        std::chrono::milliseconds aSleepValue = 200ms) noexcept;
    static void endLock() noexcept;

    static const bool& touchFlag(const std::string& aName,
                                 bool aDefaultValue = false) noexcept;
    static const int& touchInt(const std::string& aName,
                               int aDefaultValue = 0) noexcept;
    static const std::string& touchWord(
        const std::string& aName,
        const std::string& aDefaultValue = "") noexcept;

    static void setVariable(const std::string& aName, bool aValue) noexcept;
    static void setVariable(const std::string& aName, int aValue) noexcept;
    static void setVariable(const std::string& aName,
                            const std::string& aValue) noexcept;

private:
    bool mMutexFlag;
    std::unordered_map<std::string, bool> mFlags;
    std::unordered_map<std::string, int> mInts;
    std::unordered_map<std::string, std::string> mWords;

    VariableStorage() noexcept;
    static VariableStorage& getInstance() noexcept;
    void reloadSettings() noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !VARIABLE_STORAGE_HPP
