#pragma once

//--------------------------------------------------------------------------------

#include <unordered_map>

#include "hash_map_by_str.hpp"
#include "holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class CallbackStorage
{
public:
    HOLY_TRINITY_SINGLE(CallbackStorage);

    static void add(const char* aVolumeName,
                    const char* aNodeName,
                    void* aFunc) noexcept;

    static void* get(const char* aVolumeName, const char* aNodeName) noexcept;

    static const std::unordered_map<std::string_view, void*>&
    getVolumeCallbacks(const char* aVolumeName) noexcept;

private:
    CallbackStorage() noexcept;
    static CallbackStorage& getInstance() noexcept;

    //----------------------------------------------------------------------------

    void addNonstatic(const char* aVolumeName,
                      const char* aNodeName,
                      void* aFunc) noexcept;

    void* getNonstatic(const char* aVolumeName,
                       const char* aNodeName) const noexcept;

    const std::unordered_map<std::string_view, void*>&
    getVolumeCallbacksNonstatic(const char* aVolumeName) noexcept;

    //----------------------------------------------------------------------------

    inline static const char VOLUME_NAME[] = "CallbackVolumeStorage";
    inline static const char NODE_NAME[]   = "CallbackNodeStorage";
    inline static const char NUN_NAME[]    = "NUN";

    HashMapByStr<VOLUME_NAME, 200, HashMapByStr<NODE_NAME, 200, void*>> m_map;
};
} // namespace core

//--------------------------------------------------------------------------------
