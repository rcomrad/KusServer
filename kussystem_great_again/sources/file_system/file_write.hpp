#pragma once

//--------------------------------------------------------------------------------

#include <map>
#include <optional>
#include <unordered_set>

#include "string/kus_string.hpp"

#include "read_target.hpp"

//--------------------------------------------------------------------------------

namespace fs
{

class FileWrite
{
public:
    FileWrite() noexcept = delete;

    static bool writeData(const char* aFileName, const char* aData) noexcept;
    // static std::optional<str::String> writeData(
    //     const char* aFolderName,
    //     const char* aFileName,
    //     const char* aData) noexcept;

private:
    static str::String readFile(const char* aPath) noexcept;
};

} // namespace fs

//--------------------------------------------------------------------------------
