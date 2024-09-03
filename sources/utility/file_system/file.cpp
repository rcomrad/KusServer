#include "file.hpp"

#include <fstream>
#include <iostream>

#include "path_storage.hpp"

std::optional<std::string>
util::File::read(std::string_view a_path) noexcept
{
    std::optional<std::string> result;
    std::ifstream file(a_path.data());
    if (file.is_open())
    {
        std::string temp;
        std::getline(file, temp, '\0');
        result = std::move(temp);
    }
    return result;
}

std::optional<std::string>
util::File::readStored(std::string_view a_path) noexcept
{
    std::optional<std::string> result;
    DECLARE_LOCAL_CONTEXT;
    auto path = PathStorage::getFilePath(a_path, &context_local);
    if (path.has_value())
    {
        result = read(path.value());
    }
    return result;
}
