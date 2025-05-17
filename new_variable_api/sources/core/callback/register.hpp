#pragma once

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_set>

//--------------------------------------------------------------------------------

namespace core
{
class CallbackRegister
{
protected:
    struct Info
    {
        std::string volume_name;
        std::string node_name;
        void* func;
    };
    using CallbackInfoArray = std::unordered_set<core::CallbackRegister::Info>;

    static void registerCallback(std::string&& a_volume_name,
                                 std::string&& a_node_name,
                                 void* a_func) noexcept;
    static void registerCallback(CallbackInfoArray&& a_info_array) noexcept;
};

} // namespace core

//--------------------------------------------------------------------------------
