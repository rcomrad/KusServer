#include "callback_storage.hpp"

#include "logging.hpp"

SINGLETON_DEFINITOR(core, CallbackStorage);

//------------------------------------------------------------------------------

core::CallbackStorage::CallbackStorage() noexcept
{
    mMap[""];
}

// void
// core::CallbackStorage::addNonstatic(
//     const CallbackdSettings& a_settings) noexcept
// {
//     mMap[a_settings.volume_ame][a_settings.node_name] = a_settings.func;
// }

void
core::CallbackStorage::addNonstatic(const str::string& a_volume_ame,
                                    const str::string& a_node_name,
                                    void* a_func) noexcept
{
    mMap[a_volume_ame][a_node_name] = a_func;
}

void
core::CallbackStorage::addNonstatic(
    const CallBackSettingArray& a_settings) noexcept
{
    for (const auto& i : a_settings)
    {
        addNonstatic(i.volume_ame, i.node_name, i.func);
    }
}

void*
core::CallbackStorage::getNonstatic(const str::string& aVolumeName,
                                    const str::string& aNodeName) noexcept
{
    void* result = nullptr;

    auto it1 = mMap.find(aVolumeName);
    if (it1 != mMap.end())
    {
        auto it2 = it1->second.find(aNodeName);
        if (it2 != it1->second.end())
        {
            result = it2->second;
            LOG_INFO("Return callback node '%s' from volume '%s'", aVolumeName,
                     aNodeName);
        }
        else
        {
            // TODO: default callback
            LOG_ERROR("No '%s' callback node in '%s' volume", aNodeName,
                      aVolumeName);
        }
    }
    else
    {
        LOG_ERROR("No '%s' callback volume ", aVolumeName);
    }

    return result;
}

core::CallbackStorage::VolumeDict
core::CallbackStorage::getVolumeCallbacksNonstatic(
    const str::string& aVolumeName) noexcept
{
    auto it = mMap.find(aVolumeName);
    if (it != mMap.end() && !aVolumeName.empty())
    {
        return it->second;
        LOG_INFO("Return '%s' callback volume", aVolumeName);
    }
    else
    {
        LOG_ERROR("No '%s' callback volume ", aVolumeName);
        it = mMap.find("");
        return it->second;
    }
}

//------------------------------------------------------------------------------
