#pragma once

//--------------------------------------------------------------------------------

#include <unordered_map>

#include "domain/holy_trinity.hpp"

#include "string/kus_string.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class CallbackStorage
{
public:
    static str::string MODULE_CALLBACK_VOLUME;

    static void add(const str::string& aVolumeName,
                    const str::string& aNodeName,
                    void* aFunc) noexcept;

    static void* get(const str::string& aVolumeName,
                     const str::string& aNodeName) noexcept;

    static const std::unordered_map<str::string, void*>& getVolumeCallbacks(
        const str::string& aVolumeName) noexcept;

private:
    HOLY_TRINITY_SINGLE(CallbackStorage);

    CallbackStorage() noexcept;
    static CallbackStorage& getInstance() noexcept;

    //----------------------------------------------------------------------------

    void addNonstatic(const str::string& aVolumeName,
                      const str::string& aNodeName,
                      void* aFunc) noexcept;

    void* getNonstatic(const str::string& aVolumeName,
                       const str::string& aNodeName) const noexcept;

    const std::unordered_map<str::string, void*>& getVolumeCallbacksNonstatic(
        const str::string& aVolumeName) noexcept;

    //----------------------------------------------------------------------------

    std::unordered_map<str::string, std::unordered_map<str::string, void*>>
        mMap;
};
} // namespace core

//--------------------------------------------------------------------------------
