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

    static bool writeData(const str::string& aFileName,
                          const str::string& aData) noexcept;
    // static std::optional<str::string> writeData(
    //     const str::string& aFolderName,
    //     const str::string& aFileName,
    //     const str::string& aData) noexcept;

private:
    static str::string readFile(const str::string& aPath) noexcept;
};

} // namespace fs

//--------------------------------------------------------------------------------
