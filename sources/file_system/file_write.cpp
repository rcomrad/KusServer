#include "file_write.hpp"

#include <fstream>

#include "core/logging.hpp"
#include "string/separators.hpp"

#include "path.hpp"

bool
file::FileWrite::writeData(const std::string& aFileName,
                           const std::string& aData) noexcept
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

// std::optional<std::string>
// file::File::writeData(const std::string& aFolderName,
//                       const std::string& aFileName,
//                       const std::string& aData) noexcept
// {
//     std::optional<std::string> result;

//     auto path = core::Path::touchFolder(aFolderName);
//     if (path.has_value())
//     {
//         result = path.value() + aFileName;
//         writeData(result.value(), aData);
//     }

//     return result;
// }
