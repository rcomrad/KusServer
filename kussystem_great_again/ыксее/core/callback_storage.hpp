// #pragma once

// //--------------------------------------------------------------------------------

// #include <unordered_map>

// #include "string/kus_string.hpp"

// #include "holy_trinity.hpp"

// //--------------------------------------------------------------------------------

// namespace core
// {
// class CallbackStorage
// {
// public:
//     HOLY_TRINITY_SINGLE(CallbackStorage);

//     static void add(const char* aVolumeName,
//                     const char* aNodeName,
//                     void* aFunc) noexcept;

//     static void* get(const char* aVolumeName,
//                      const char* aNodeName) noexcept;

//     static const std::unordered_map<str::String, void*>& getVolumeCallbacks(
//         const char* aVolumeName) noexcept;

// private:
//     CallbackStorage() noexcept;
//     static CallbackStorage& getInstance() noexcept;

//     //----------------------------------------------------------------------------

//     void addNonstatic(const char* aVolumeName,
//                       const char* aNodeName,
//                       void* aFunc) noexcept;

//     void* getNonstatic(const char* aVolumeName,
//                        const char* aNodeName) const noexcept;

//     const std::unordered_map<str::String, void*>&
//     getVolumeCallbacksNonstatic(
//         const char* aVolumeName) noexcept;

//     //----------------------------------------------------------------------------

//     // std::unordered_map<str::String, std::unordered_map<str::String,
//     void*>>
//     //     mMap;
// };
// } // namespace core

// //--------------------------------------------------------------------------------
