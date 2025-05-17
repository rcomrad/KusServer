#include "file.hpp"

#include <fstream>
#include <iostream>

#include "kernel/framework/module/kernel.hpp"

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
    auto& path = KERNEL.getFilePath(std::string(a_path));
    result     = read(path);
    return result;
}
