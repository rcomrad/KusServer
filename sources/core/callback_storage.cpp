#include "callback_storage.hpp"

#include "logging.hpp"

//------------------------------------------------------------------------------

core::CallbackStorage::CallbackStorage() noexcept
{
    mMap[""];
}

void
core::CallbackStorage::addNonstatic(const str::string& aVolumeName,
                                    const str::string& aNodeName,
                                    void* aFunc) noexcept
{
    mMap[aVolumeName][aNodeName] = aFunc;
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
            LOG_INFO("Return callback node (", "volume:", aVolumeName,
                     "node:", aNodeName, ")");
        }
        else
        {
            // TODO: default callback
            LOG_ERROR("No such callback node (", "volume:", aVolumeName,
                      "node:", aNodeName, ")");
        }
    }
    else
    {
        LOG_ERROR("No such callback volume (", aVolumeName, ")");
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
        LOG_INFO("Return callback volume (", aVolumeName, ")");
    }
    else
    {
        LOG_ERROR("No such callback volume (", aVolumeName, ")");
        it = mMap.find("");
        return it->second;
    }
}

//------------------------------------------------------------------------------
