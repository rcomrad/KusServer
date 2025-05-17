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

namespace file
{
class VariableStorage
{
public:
    HOLY_TRINITY_SINGLE(VariableStorage);
    static VariableStorage& getInstance() noexcept;

    std::optional<bool> getFlag(const char* aName) const noexcept;
    std::optional<int> getInt(const char* aName) const noexcept;
    boost::optional<const char*> getWord(const char* aName) const noexcept;

    bool getFlagUnsafe(const char* aName, bool aDefault = false) const noexcept;
    int getIntUnsafe(const char* aName, int aDefault = 0) const noexcept;
    const char* getWordUnsafe(const char* aName,
                              const char* aDefault = "") const noexcept;

    void setVariable(const char* aName, bool aValue) noexcept;
    void setVariable(const char* aName, int aValue) noexcept;
    void setVariable(const char* aName, const char* aValue) noexcept;

private:
    VariableStorage() noexcept;

    void reloadSettings() noexcept;

    mutable std::mutex mBoolMutex;
    std::unordered_map<str::String, bool> mFlags;

    mutable std::mutex mIntMutex;
    std::unordered_map<str::String, int> mInts;

    mutable std::mutex mWordMutex;
    std::unordered_map<str::String, str::String> mWords;
};
} // namespace file

//--------------------------------------------------------------------------------

#endif // !VARIABLE_STORAGE_HPP
