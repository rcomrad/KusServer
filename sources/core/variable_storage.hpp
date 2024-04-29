#pragma once

// //--------------------------------------------------------------------------------

// #include <string>
// #include <unordered_map>

// #include "domain/holy_trinity.hpp"
// #include "domain/metaprogramming.hpp"

// using namespace std::chrono_literals;

// //--------------------------------------------------------------------------------

// namespace core
// {
// class VariableStorage
// {
// public:
//     HOLY_TRINITY_SINGLE(VariableStorage);


//     static void setVariable(
//         const str::string& aName,
//         bool aValue,
//         std::chrono::milliseconds aSleepValue = 200ms) noexcept;
//     static void setVariable(
//         const str::string& aName,
//         int aValue,
//         std::chrono::milliseconds aSleepValue = 200ms) noexcept;

//     template <typename S, typename = dom::enableIf<dom::isString<S>>>
//     static void setVariable(
//         const str::string& aName,
//         S&& aValue,
//         std::chrono::milliseconds aSleepValue = 200ms) noexcept
//     {
//         static VariableStorage& instance = getInstance();
//         if (instance.mMutexFlag == false)
//         {
//             instance.beginLock(aSleepValue);
//             instance.mWords[aName] = std::forward<S>(aValue);
//             instance.endLock();
//         }
//         else
//         {
//             instance.mWords[aName] = std::forward<S>(aValue);
//         }
//     }

// private:
//     bool mMutexFlag;
//     std::unordered_map<str::string, bool> mFlags;
//     std::unordered_map<str::string, int> mInts;
//     std::unordered_map<str::string, str::string> mWords;

//     VariableStorage() noexcept;
//     static VariableStorage& getInstance() noexcept;
//     void reloadSettings() noexcept;
// };
// } // namespace core

// //--------------------------------------------------------------------------------

// #endif // !VARIABLE_STORAGE_HPP
