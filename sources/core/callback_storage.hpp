#pragma once

//--------------------------------------------------------------------------------

#include <unordered_map>

#include "string/kus_string.hpp"

#include "holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class CallbackStorage
{
private:
    using VolumeDict = const std::unordered_map<str::string, void*>&;

public:
    HOLY_TRINITY_SINGLETON(CallbackStorage);

    SINGL_VOID_METHOD(add,
                      (const str::string& aVolumeName,
                       const str::string& aNodeName,
                       void* aFunc));

    // TODO: const
    SINGL_RET_METHOD(void*,
                     get,
                     (const str::string& aVolumeName,
                      const str::string& aNodeName));

    SINGL_RET_METHOD(VolumeDict,
                     getVolumeCallbacks,
                     (const str::string& aVolumeName));

private:
    CallbackStorage() noexcept;

    std::unordered_map<str::string, std::unordered_map<str::string, void*>>
        mMap;
};
} // namespace core

//--------------------------------------------------------------------------------
