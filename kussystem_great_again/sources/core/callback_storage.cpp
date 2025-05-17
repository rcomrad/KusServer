#include "callback_storage.hpp"

#include "logging.hpp"

//------------------------------------------------------------------------------

core::CallbackStorage::CallbackStorage() noexcept
{
    m_map[NUN_NAME];
}

core::CallbackStorage&
core::CallbackStorage::getInstance() noexcept
{
    static CallbackStorage instance;
    return instance;
}

//------------------------------------------------------------------------------

void
core::CallbackStorage::add(const char* aVolumeName,
                           const char* aNodeName,
                           void* aFunc) noexcept
{
    getInstance().addNonstatic(aVolumeName, aNodeName, aFunc);
}

void
core::CallbackStorage::addNonstatic(const char* a_volume_name,
                                    const char* a_node_name,
                                    void* a_func) noexcept
{
    m_map[a_volume_name][a_node_name] = a_func;
}

//------------------------------------------------------------------------------

void*
core::CallbackStorage::get(const char* aVolumeName,
                           const char* aNodeName) noexcept
{
    return getInstance().getNonstatic(aVolumeName, aNodeName);
}

void*
core::CallbackStorage::getNonstatic(const char* aVolumeName,
                                    const char* aNodeName) const noexcept
{
    void* result = nullptr;

    auto callback = m_map.get(aVolumeName, aNodeName);
    // TODO: default callback
    if (callback)
    {
        result = callback.getValue();
    }

    return result;
}

//------------------------------------------------------------------------------

// const decltype(*m_map.get(NUN_NAME).getPtr())&
// core::CallbackStorage::getVolumeCallbacks(
//     const char* aVolumeName) const noexcept
// {
//     return getInstance().getVolumeCallbacksNonstatic(aVolumeName);
// }

const core::CallbackStorage::VolumeType&
core::CallbackStorage::getVolumeCallbacks(
    const char* aVolumeName) noexcept
{
    return getInstance().getVolumeCallbacksNonstatic(aVolumeName);
}

const core::CallbackStorage::VolumeType&
core::CallbackStorage::getVolumeCallbacksNonstatic(
    const char* aVolumeName) const noexcept
{
    auto volume = m_map.get(aVolumeName);
    if (volume)
    {
        LOG_INFO("Return callback volume (", aVolumeName, ")");
    }
    else
    {
        LOG_ERROR("No such callback volume (", aVolumeName, ")");
        volume = m_map.get(NUN_NAME);
    }

    return *volume.getPtr();
}

//------------------------------------------------------------------------------
