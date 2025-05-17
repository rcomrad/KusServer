#include "file_write.hpp"

#include <fstream>

#include "core/logging.hpp"

#include "string/separators.hpp"

#include "path.hpp"

bool
fs::FileWrite::writeData(const char* aFileName, const char* aData) noexcept
{
    bool result = false;
    std::ofstream out(aFileName);
    if (out.is_open())
    {
        out << aData;
        out.close();
        result = true;
    }
    else
    {
        LOG_ERROR("Can't create file", aFileName);
    }
    return result;
}

// std::optional<str::String>
// file::File::writeData(const char* aFolderName,
//                       const char* aFileName,
//                       const char* aData) noexcept
// {
//     std::optional<str::String> result;

//     auto path = core::Path::touchFolder(aFolderName);
//     if (path.has_value())
//     {
//         result = path.value() + aFileName;
//         writeData(result.value(), aData);
//     }

//     return result;
// }
