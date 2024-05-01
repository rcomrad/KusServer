#include "read_target.hpp"

fs::ReadTarget
fs::ReadFromData(const str::string& aDta)
{
    return ReadTarget(aDta, str::EMPTY_STRING, str::EMPTY_STRING,
                      ReadTarget::Type::DATA);
}

fs::ReadTarget
fs::ReadFromFile(const str::string& aFullFileName)
{
    return ReadTarget(str::EMPTY_STRING, aFullFileName, str::EMPTY_STRING,
                      ReadTarget::Type::FILE_NAME);
}

fs::ReadTarget
fs::ReadFromFile(const str::string& aFileName, const str::string& aFolderName)
{
    return ReadTarget(str::EMPTY_STRING, aFileName, aFolderName,
                      ReadTarget::Type::FILE_LOCATION);
}
