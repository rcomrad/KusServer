// #include "read_target.hpp"

// #include "core/logging/logging.hpp"

// #include "path.hpp"

// fs::ReadTarget::ReadTarget(fs::ReadTarget::Type aType, const str::string& aData)
//     : mType(aType), mData(aData)
// {
// }

// //--------------------------------------------------------------------------------

// fs::DataTarget::DataTarget(const str::string& aData)
//     : ReadTarget(ReadTarget::Type::DATA, aData)
// {
// }

// fs::FilenameRefTarget::FilenameRefTarget(
//     const str::string& aData,
//     Type aType = ReadTarget::Type::FILE_NAME_REF)
//     : ReadTarget(aType, aData)
// {
// }

// fs::FilenameTarget::FilenameTarget(str::string&& aData,
//                                    Type aType = ReadTarget::Type::FILE_NAME)
//     : ReadTarget(aType, mFilename), mFilename(std::move(aData))
// {
// }

// //--------------------------------------------------------------------------------

// fs::DataTarget
// fs::ReadFromData(const str::string& aData)
// {
//     return {aData};
// }

// fs::FilenameRefTarget
// fs::ReadFromFilePath(const str::string& aFullFileName)
// {
//     return {aFullFileName};
// }

// fs::FilenameRefTarget
// fs::ReadFromStoredFile(const str::string& aFileName)
// {
//     auto path = Path::getFilePath(aFileName);
//     if (path.has_value())
//     {
//         return {path.value()};
//     }
//     else
//     {
//         LOG_ERROR("Can't find file '%s'", aFileName);
//         return {str::EMPTY_STRING, ReadTarget::Type::NUN};
//     }
// }

// fs::FilenameTarget
// fs::ReadFromStoredFile(const str::string& aFolderName,
//                        const str::string& aFileName)
// {
//     auto path = Path::getFilePath(aFolderName, aFileName);
//     if (path.has_value())
//     {
//         return {std::move(path.value())};
//     }
//     else
//     {
//         LOG_ERROR("Can't find file. Folder: '%s', file name: '%s'", aFolderName,
//                   aFileName);
//         return {str::string(str::EMPTY_STRING), ReadTarget::Type::NUN};
//     }
// }
