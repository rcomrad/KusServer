#pragma once

//--------------------------------------------------------------------------------

#include <tuple>
#include <unordered_set>
#include <vector>

#include "string/kus_string.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class CallbackRegister
{
public:
    CallbackRegister(const str::string& aVolumeName,
                     const str::string& aNodeName,
                     void* aFunc) noexcept;

    // RouterNode(const std::vector<std::tuple<str::string, str::string,
    // void*>>&
    //                aRouts) noexcept;

    // RouterNode(const std::vector<str::string>& aVolumeNames,
    //            const str::string& aNodeName,
    //            const std::vector<void*>& aFuncs) noexcept;

    // RouterNode(const str::string& aVolumeName,
    //            const std::unordered_set<str::string>& aNodeNames,
    //            void* aFunc) noexcept;

    // RouterNode(const str::string& aVolumeName,
    //            const std::unordered_map<str::string, void*>& aNodes)
    //            noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------
