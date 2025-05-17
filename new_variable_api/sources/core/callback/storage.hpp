#pragma once

//--------------------------------------------------------------------------------

#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include "boost/optional.hpp"
#include "utility/common/holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace core
{

class CallbackStorage
{
public:
    HOLY_TRINITY_SINGLETON(CallbackStorage);

    SINGL_VOID_METHOD(add,
                      (std::string && a_volume_name,
                       std::string&& a_node_name,
                       void* a_func));

    // TODO: const
    SINGL_RET_METHOD(void*,
                     get,
                     (std::string_view a_volume_name,
                      std::string_view a_node_name));

    using CallbackVolumeRes =
        boost::optional<const std::unordered_map<std::string_view, void*>&>;
    SINGL_RET_METHOD(CallbackVolumeRes,
                     getVolumeCallbacks,
                     (std::string_view a_volume_name));

private:
    std::unordered_set<std::string> m_names_storage;
    std::unordered_map<std::string_view,
                       std::unordered_map<std::string_view, void*>>
        m_callback_storage;

    CallbackStorage() noexcept;
};

} // namespace core

//--------------------------------------------------------------------------------
