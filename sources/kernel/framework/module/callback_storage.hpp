#pragma once

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>

//--------------------------------------------------------------------------------

namespace core
{

class CallbackStorage
{
public:
    void storeCallback(const std::string& a_volume_name,
                       const std::string& a_node_name,
                       void* a_func);

    void* searchForCallback(const std::string& a_volume_name,
                            const std::string& a_node_name) const;

private:
    using VolumeType = std::unordered_map<std::string, void*>;
    std::unordered_map<std::string, VolumeType> m_callback_storage;

    const VolumeType& getVolumeCallbacks(
        const std::string& a_volume_name) const;
};

} // namespace core

//--------------------------------------------------------------------------------
