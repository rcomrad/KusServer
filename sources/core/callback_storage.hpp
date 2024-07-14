#pragma once

//--------------------------------------------------------------------------------

#include <unordered_map>
#include <vector>

#include "string/kus_string.hpp"

#include "holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace core
{

struct CallbackdSettings
{
    const str::string& volume_ame;
    const str::string& node_name;
    void* func;
};
using CallBackSettingArray = std::vector<CallbackdSettings>;

class CallbackStorage
{
private:
    using VolumeDict = const std::unordered_map<str::string, void*>&;

public:
    HOLY_TRINITY_SINGLETON(CallbackStorage);

    // SINGL_VOID_METHOD(add, (const CallbackdSettings& a_settings));
    SINGL_VOID_METHOD(add,
                      (const str::string& a_volume_ame,
                       const str::string& a_node_name,
                       void* a_func));

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

    // void addNonstatic(const str::string& a_volume_ame,
    //                   const str::string& a_node_name,
    //                   void* a_func) noexcept;
    void addNonstatic(const CallBackSettingArray& a_settings) noexcept;

    std::unordered_map<str::string, std::unordered_map<str::string, void*>>
        mMap;
};
} // namespace core

//--------------------------------------------------------------------------------
