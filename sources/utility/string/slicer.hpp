#pragma once

//------------------------------------------------------------------------------

#include <string_view>
#include <vector>

#include "caster.hpp"

//------------------------------------------------------------------------------

namespace util
{

class Slicer
{
public:
    Slicer() = delete;

    static std::vector<std::string_view> process(
        StringCaster a_str,
        const char* a_delimiters,
        const char* a_erase = "") noexcept;
    // TODO: const a_from_str
    static std::vector<std::string_view> safeProcess(
        StringCaster a_from_str,
        StringCaster a_to_str,
        const char* a_delimiters,
        const char* a_erase = "") noexcept;

private:
    static std::vector<std::string_view> baseProcess(
        StringCaster a_from_str,
        StringCaster a_to_str,
        const char* a_delimiters,
        const char* a_erase) noexcept;
};

} // namespace util

//------------------------------------------------------------------------------
