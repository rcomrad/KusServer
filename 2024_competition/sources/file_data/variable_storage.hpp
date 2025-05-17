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

    std::optional<bool> getFlag(const std::string& aName) const noexcept;
    std::optional<int> getInt(const std::string& aName) const noexcept;
    boost::optional<const std::string&> getWord(
        const std::string& aName) const noexcept;

    bool getFlagUnsafe(const std::string& aName,
                       bool aDefault = false) const noexcept;
    int getIntUnsafe(const std::string& aName, int aDefault = 0) const noexcept;
    const std::string& getWordUnsafe(
        const std::string& aName,
        const std::string& aDefault = "") const noexcept;

    void setVariable(const std::string& aName, bool aValue) noexcept;
    void setVariable(const std::string& aName, int aValue) noexcept;
    void setVariable(const std::string& aName,
                     const std::string& aValue) noexcept;

private:
    VariableStorage() noexcept;

    void reloadSettings() noexcept;

    mutable std::mutex mBoolMutex;
    std::unordered_map<std::string, bool> mFlags;

    mutable std::mutex mIntMutex;
    std::unordered_map<std::string, int> mInts;

    mutable std::mutex mWordMutex;
    std::unordered_map<std::string, std::string> mWords;
};
} // namespace file

//--------------------------------------------------------------------------------

#endif // !VARIABLE_STORAGE_HPP
