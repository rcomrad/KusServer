#pragma once

//--------------------------------------------------------------------------------

#include <unordered_map>

#include "kus_standard/double_map_by_str.hpp"

#include "holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class CallbackStorage
{
private:
    inline static const char STORAGE_NAME[] = "CallbacStorage";
    inline static const char NUN_NAME[]     = "NUN";
    kstd::DoubleMapByStr<STORAGE_NAME, 200, void*> m_map;

    using VolumeType = decltype(*m_map.get(NUN_NAME).getPtr());

public:
    HOLY_TRINITY_SINGLE(CallbackStorage);

    static void add(const char* aVolumeName,
                    const char* aNodeName,
                    void* aFunc) noexcept;

    static void* get(const char* aVolumeName, const char* aNodeName) noexcept;

    static const VolumeType& getVolumeCallbacks(
        const char* aVolumeName) noexcept;

private:
    CallbackStorage() noexcept;
    static CallbackStorage& getInstance() noexcept;

    //----------------------------------------------------------------------------

    void addNonstatic(const char* aVolumeName,
                      const char* aNodeName,
                      void* aFunc) noexcept;

    void* getNonstatic(const char* aVolumeName,
                       const char* aNodeName) const noexcept;

    const VolumeType& getVolumeCallbacksNonstatic(
        const char* aVolumeName) const noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------
