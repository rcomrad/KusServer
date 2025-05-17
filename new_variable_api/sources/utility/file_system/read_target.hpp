// #pragma once

// //--------------------------------------------------------------------------------

// #include "string/kus_string.hpp"

// #include "utility/common/holy_trinity.hpp"

// //--------------------------------------------------------------------------------

// namespace fs
// {

// struct ReadTarget
// {
//     HOLY_TRINITY_NOCOPY(ReadTarget);

//     enum Type
//     {
//         NUN,
//         DATA,
//         FILE_NAME,
//         FILE_NAME_REF
//     };

//     Type mType;
//     const str::string& mData;

//     ReadTarget(Type aType, const str::string& aData);
// };

// //--------------------------------------------------------------------------------

// struct DataTarget : public ReadTarget
// {
//     HOLY_TRINITY_NOCOPY(DataTarget);
//     DataTarget(const str::string& aData);
// };

// struct FilenameRefTarget : public ReadTarget
// {
//     HOLY_TRINITY_NOCOPY(FilenameRefTarget);
//     FilenameRefTarget(const str::string& aData, Type aType);
// };

// struct FilenameTarget : public ReadTarget
// {
//     str::string mFilename;

//     HOLY_TRINITY_NOCOPY(FilenameTarget);
//     FilenameTarget(str::string&& aData, Type aType);
// };

// //--------------------------------------------------------------------------------

// DataTarget
// ReadFromData(const str::string& aData);

// FilenameRefTarget
// ReadFromFilePath(const str::string& aFullFileName);

// FilenameRefTarget
// ReadFromStoredFile(const str::string& aFileName);

// FilenameTarget
// ReadFromStoredFile(const str::string& aFolderName,
//                    const str::string& aFileName);

// } // namespace fs

// //--------------------------------------------------------------------------------
