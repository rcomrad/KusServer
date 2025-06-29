#pragma once

//------------------------------------------------------------------------------

#include <string>
#include <string_view>
#include <vector>

//------------------------------------------------------------------------------

namespace util
{

class Slicer
{
public:
    Slicer() = delete;

    static std::vector<std::string> copy(std::string_view a_str,
                                         const char* a_delimiters);

    static std::vector<std::string> copy(std::string_view a_str,
                                         const char* a_delimiters,
                                         const char* a_erase);

    static std::vector<std::string_view> change(std::string_view a_str,
                                                const char* a_delimiters);

    static std::vector<std::string_view> change(std::string_view a_str,
                                                const char* a_delimiters,
                                                const char* a_erase);
};

} // namespace util

//------------------------------------------------------------------------------
