#ifndef VARIABLE_STORAGE_HPP
#define VARIABLE_STORAGE_HPP

//--------------------------------------------------------------------------------

#include <chrono>
#include <string>
#include <unordered_map>

#include "holy_trinity.hpp"
#include "metaprogramming.hpp"

using namespace std::chrono_literals;

//--------------------------------------------------------------------------------

namespace dom
{
class VariableStorage
{
public:
    HOLY_TRINITY_SINGLE(VariableStorage);

    static bool isLocked() noexcept;
    static void beginLock(
        std::chrono::milliseconds aSleepValue = 200ms) noexcept;
    static void endLock() noexcept;

    //----------------------------------------------------------------------------

    static const bool& touchFlag(const std::string& aName,
                                 bool aDefaultValue = false) noexcept;
    static const int& touchInt(const std::string& aName,
                               int aDefaultValue = 0) noexcept;

    // TODO: fix
    // template <typename S, typename = dom::enableIf<dom::isString<S>>>
    // static const std::string& touchWord(const std::string& aName,
    //                                     S&& aDefaultValue = "") noexcept

    static const std::string& touchWord(
        const std::string& aName, std::string&& aDefaultValue = "") noexcept
    {
        static VariableStorage& instance = getInstance();
        return instance.touch(aName, instance.mWords,
                              std::forward<std::string>(aDefaultValue));
    }

    //----------------------------------------------------------------------------

    static void setVariable(
        const std::string& aName,
        bool aValue,
        std::chrono::milliseconds aSleepValue = 200ms) noexcept;
    static void setVariable(
        const std::string& aName,
        int aValue,
        std::chrono::milliseconds aSleepValue = 200ms) noexcept;

    template <typename S, typename = dom::enableIf<dom::isString<S>>>
    static void setVariable(
        const std::string& aName,
        S&& aValue,
        std::chrono::milliseconds aSleepValue = 200ms) noexcept
    {
        static VariableStorage& instance = getInstance();
        instance.set(aName, instance.mWords, std::forward<S>(aValue),
                     aSleepValue);
    }

    //----------------------------------------------------------------------------

private:
    bool mMutexFlag;
    std::unordered_map<std::string, bool> mFlags;
    std::unordered_map<std::string, int> mInts;
    std::unordered_map<std::string, double> mDouble;
    std::unordered_map<std::string, std::string> mWords;

    //----------------------------------------------------------------------------

    VariableStorage() noexcept;
    static VariableStorage& getInstance() noexcept;
    void reloadSettings() noexcept;

    //----------------------------------------------------------------------------

    template <typename T>
    void set(const std::string& aName,
             std::unordered_map<std::string, T>& aVariables,
             T&& aValue,
             std::chrono::milliseconds aSleepValue) noexcept
    {
        if (mMutexFlag == false)
        {
            beginLock(aSleepValue);
            aVariables[aName] = std::forward<T>(aValue);
            endLock();
        }
        else
        {
            aVariables[aName] = std::forward<T>(aValue);
        }
    }

    template <typename T>
    T& touch(const std::string& aName,
             std::unordered_map<std::string, T>& aVariables,
             T&& aDefaultValue) noexcept
    {
        auto it = aVariables.find(aName);
        if (it != aVariables.end())
        {
            return it->second;
        }
        return aVariables.insert({aName, std::forward<T>(aDefaultValue)})
            .first->second;
    }
};
} // namespace dom

//--------------------------------------------------------------------------------

#endif // !VARIABLE_STORAGE_HPP
