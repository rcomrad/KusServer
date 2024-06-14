#pragma once

//--------------------------------------------------------------------------------

#include <string>

#include "core/holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace str
{

struct String : public std::string
{
private:
    size_t calculateSize(const String& s) noexcept
    {
        return s.size();
    }

public:
    String() noexcept;
    String(int size) noexcept;
    String(const char* s) noexcept;
    // String(const String& first, const String& second) noexcept;
    String& operator=(const char* s) noexcept;
    // String& operator=(std::string&& s) noexcept;

    HOLY_TRINITY_NOCOPY(String);

    static String EMPTY_STRING;

    template <typename... Args>
    String substr(Args... args) const noexcept
    {
        return std::string::substr(args...);
    }

    const std::string& getStdStringRef() const noexcept;

    // void addBack(const String& s) noexcept
    // {
    // }

    // template <typename Args>
    // void addBack(const Args&... args)
    // {
    // }
};
} // namespace str

// #define string no_more_std_string

//--------------------------------------------------------------------------------
