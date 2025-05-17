#include "register.hpp"

#include "storage.hpp"

void
core::CallbackRegister::registerCallback(std::string&& a_volume_name,
                                         std::string&& a_node_name,
                                         void* a_func) noexcept
{
    CallbackStorage::add(std::move(a_volume_name), std::move(a_node_name),
                         a_func);
}

void
core::CallbackRegister::registerCallback(
    CallbackInfoArray&& a_info_array) noexcept
{
    for (auto&& i : a_info_array)
    {
        std::string gg1 = i.volume_name;
        std::string gg2 = i.node_name;
        CallbackStorage::add(std::move(gg1), std::move(gg2), i.func);
    }
}
