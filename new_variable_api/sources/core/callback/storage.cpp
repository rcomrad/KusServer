#include "storage.hpp"

#include "core/logging/logging.hpp"

SINGLETON_DEFINITOR(core, CallbackStorage);

//------------------------------------------------------------------------------

core::CallbackStorage::CallbackStorage() noexcept
{
}

void
core::CallbackStorage::addNonstatic(std::string&& a_volume_name,
                                    std::string&& a_node_name,
                                    void* a_func) noexcept
{
    auto vol  = m_names_storage.insert(std::move(a_volume_name)).first;
    auto node = m_names_storage.insert(std::move(a_node_name)).first;

    m_callback_storage[*vol][*node] = a_func;
}

void*
core::CallbackStorage::getNonstatic(std::string_view a_volume_name,
                                    std::string_view a_node_name) noexcept
{
    void* result = nullptr;

    auto vol_opt = getVolumeCallbacks(a_volume_name);
    if (vol_opt.has_value())
    {
        const auto& vol = vol_opt.value();
        auto it         = vol.find(a_node_name);
        if (it != vol.end())
        {
            result = it->second;
            LOG_INFO("Return callback node '%s' from volume '%s'",
                     a_volume_name, a_node_name);
        }
        else
        {
            // TODO: default callback?
            LOG_ERROR("No '%s' callback node in '%s' volume", a_node_name,
                      a_volume_name);
        }
    }

    return result;
}

core::CallbackStorage::CallbackVolumeRes
core::CallbackStorage::getVolumeCallbacksNonstatic(
    std::string_view a_volume_name) noexcept
{
    CallbackVolumeRes result;

    auto it = m_callback_storage.find(a_volume_name);
    if (it != m_callback_storage.end() && !a_volume_name.empty())
    {
        LOG_INFO("Return '%s' callback volume", a_volume_name);
        result = it->second;
    }
    else
    {
        LOG_ERROR("No '%s' callback volume ", a_volume_name);
    }
    return result;
}

//------------------------------------------------------------------------------
