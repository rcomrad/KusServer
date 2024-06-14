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

    std::optional<bool> getFlag(const str::String& aName) const noexcept;
    std::optional<int> getInt(const str::String& aName) const noexcept;
    boost::optional<const str::String&> getWord(
        const str::String& aName) const noexcept;

    bool getFlagUnsafe(const str::String& aName,
                       bool aDefault = false) const noexcept;
    int getIntUnsafe(const str::String& aName, int aDefault = 0) const noexcept;
    const str::String& getWordUnsafe(
        const str::String& aName,
        const str::String& aDefault = "") const noexcept;

    void setVariable(const str::String& aName, bool aValue) noexcept;
    void setVariable(const str::String& aName, int aValue) noexcept;
    void setVariable(const str::String& aName,
                     const str::String& aValue) noexcept;

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
