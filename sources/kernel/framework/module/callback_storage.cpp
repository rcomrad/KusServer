#include "callback_storage.hpp"

#include <stdexcept>

#include "kernel/framework/logging/logging.hpp"

//------------------------------------------------------------------------------

void
core::CallbackStorage::storeCallback(const std::string& a_volume_name,
                                     const std::string& a_node_name,
                                     void* a_func)
{
    m_callback_storage[a_volume_name][a_node_name] = a_func;
}

void*
core::CallbackStorage::searchForCallback(const std::string& a_volume_name,
                                         const std::string& a_node_name) const
{

    auto& vol = getVolumeCallbacks(a_volume_name);
    auto it   = vol.find(a_node_name);

    if (it == vol.end())
    {
        LOG_ERROR("No '%s' callback node in '%s' volume", a_node_name,
                  a_volume_name);
    }
    else
    {
        LOG_INFO("Return callback node '%s' from volume '%s'", a_volume_name,
                 a_node_name);
    }

    return it->second;
}

const core::CallbackStorage::VolumeType&
core::CallbackStorage::getVolumeCallbacks(
    const std::string& a_volume_name) const
{
    auto it = m_callback_storage.find(a_volume_name);
    if (it == m_callback_storage.end())
    {
        LOG_ERROR("No '%s' callback volume ", a_volume_name);
        throw std::runtime_error("No such command volume");
    }
    else
    {
        LOG_INFO("Return '%s' callback volume", a_volume_name);
    }
    return it->second;
}

//------------------------------------------------------------------------------
