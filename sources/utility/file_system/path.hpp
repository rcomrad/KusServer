#pragma once

//------------------------------------------------------------------------------

#include <string>
#include <string_view>

#include "core/logging/logging.hpp"

#include "utility/common/holy_trinity.hpp"

static inline constexpr const char PATH_SEPARATOR = '/';

//------------------------------------------------------------------------------

namespace util
{
class Path
{
public:
    HOLY_TRINITY_NO_OBJECT(Path);

public:
    template <typename... Args>
    static std::string combine(bool is_folder, Args... args) noexcept
    {
        return combineImpl(is_folder, std::string_view(args)...);
    }

    static std::string getName(std::string_view a_path,
                               const core::Context& a_context) noexcept;

    static std::string normalizeFolderPath(std::string_view a_path,
                                           bool sep_postfix) noexcept;

    static std::string normalizeSeparators(std::string_view a_path) noexcept;

    static std::string getRelativeToApp(std::string_view a_path,
                                        bool is_folder) noexcept;

private:
    template <typename... Args>
    static std::string combineImpl(bool is_folder, Args... args) noexcept
    {
        std::string result;
        size_t result_size = (args.size() + ...);
        result.reserve(result_size);
        ((result += args, result.back() == PATH_SEPARATOR
                              ? void()
                              : result.push_back(PATH_SEPARATOR)),
         ...);
        if (!is_folder && !result.empty())
        {
            result.pop_back();
        }
        return result;
    }
};
} // namespace util

#define GET_PATH_LAST_NAME(a_path) util::Path::getName(a_path, LOCAL_CONTEXT)

//------------------------------------------------------------------------------
