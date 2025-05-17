#include "read_target.hpp"

#include "core/logging.hpp"

#include "path.hpp"

fs::ReadTarget::ReadTarget(fs::ReadTarget::Type aType, const char* aData)
    : mType(aType), mData(aData)
{
}

//--------------------------------------------------------------------------------

fs::DataTarget::DataTarget(const char* aData)
    : ReadTarget(ReadTarget::Type::DATA, aData)
{
}

fs::FilenameRefTarget::FilenameRefTarget(
    const char* aData,
    Type aType = ReadTarget::Type::FILE_NAME_REF)
    : ReadTarget(aType, aData)
{
}

fs::FilenameTarget::FilenameTarget(char*& aData,
                                   Type aType = ReadTarget::Type::FILE_NAME)
    : ReadTarget(aType, mFilename), mFilename(std::move(aData))
{
}

//--------------------------------------------------------------------------------

fs::DataTarget
fs::ReadFromData(const char* aData)
{
    return {aData};
}

fs::FilenameRefTarget
fs::ReadFromFilePath(const char* aFullFileName)
{
    return {aFullFileName};
}

fs::FilenameRefTarget
fs::ReadFromStoredFile(const char* aFileName)
{
    auto path = Path::getFilePath(aFileName);
    if (path.has_value())
    {
        return {path.value()};
    }
    else
    {
        LOG_ERROR("Can't find file (", aFileName, ")");
        return {str::String::EMPTY_STRING, ReadTarget::Type::NUN};
    }
}

fs::FilenameTarget
fs::ReadFromStoredFile(const char* aFolderName, const char* aFileName)
{
    auto path = Path::getFilePath(aFolderName, aFileName);
    if (path.has_value())
    {
        return {std::move(path.value())};
    }
    // else
    // {
    //     LOG_ERROR("Can't find file (Folder:", aFolderName, "Name:",
    //     aFileName,
    //               ")");
    //     return {str::String(str::EMPTY_STRING), ReadTarget::Type::NUN};
    // }
}
