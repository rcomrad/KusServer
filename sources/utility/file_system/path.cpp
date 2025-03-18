#include "path.hpp"

#include <algorithm>

#include "path_storage.hpp"
#include "path_values.hpp"

std::string
util::Path::getName(std::string_view a_path,
                    const core::Context& a_context) noexcept
{
    std::string result;
    result.reserve(a_path.size());
    int start = a_path.size() - 1;
    if (a_path[start] == PATH_SEPARATOR)
    {
        --start;
    }
    for (int i = start; i >= 0; --i)
    {
        if (a_path[i] != PATH_SEPARATOR)
        {
            result.push_back(a_path[i]);
        }
        else
        {
            break;
        }
    }
    if (result.empty())
    {
        CONTEXT_ERROR(a_context,
                      "There is no file or folder at the end of the path: '%s'",
                      a_path);
    }
    else
    {
        std::reverse(result.begin(), result.end());
    }
    return result;
}

std::string
util::Path::normalizeFolderPath(std::string_view a_path,
                                bool sep_postfix) noexcept
{
    std::string result(a_path);
    if (!result.empty())
    {
        if (sep_postfix)
        {
            if (result.back() != PATH_SEPARATOR)
            {
                result.push_back(PATH_SEPARATOR);
            }
        }
        else
        {
            if (result.back() == PATH_SEPARATOR)
            {
                result.pop_back();
            }
        }
    }

    return result;
}

std::string
util::Path::getRelativeToApp(std::string_view a_path, bool is_folder) noexcept
{
    std::string result;
    DECLARE_LOCAL_CONTEXT;
    auto app_path =
        PathStorage::getFolderPath(util::APP_PATH_NAME, &context_local);
    result = combine(is_folder, app_path.value(), a_path);
    return result;
}

std::string
util::Path::normalizeSeparators(std::string_view a_path) noexcept
{
    std::string result;
    auto size = a_path.size();

    result.reserve(size);

    for (int i = 0; i < size; ++i)
    {
        if (a_path[i] == '\\')
        {
            result.push_back('/');
        }
        else
        {
            result.push_back(a_path[i]);
        }
    }
    return result;
}
