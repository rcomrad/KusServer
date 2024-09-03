#pragma once

//------------------------------------------------------------------------------

#include <optional>
#include <string>
#include <string_view>

#include "utility/common/holy_trinity.hpp"

//------------------------------------------------------------------------------

namespace util
{

class File
{
public:
    HOLY_TRINITY_NO_OBJECT(File);
    static std::optional<std::string> read(std::string_view a_path) noexcept;
    static std::optional<std::string> readStored(
        std::string_view a_path) noexcept;
};

} // namespace util

//--------------------------------------------------------------------------------
