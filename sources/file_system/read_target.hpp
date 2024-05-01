#pragma once

//--------------------------------------------------------------------------------

#include "string/kus_string.hpp"

//--------------------------------------------------------------------------------

namespace fs
{

struct ReadTarget
{
    enum Type
    {
        NUN,
        DATA,
        FILE_NAME,
        FILE_LOCATION
    };

    const str::string& mData;
    const str::string& mFileName;
    const str::string& mFolderName;
    Type mType;
};

ReadTarget
ReadFromData(const str::string& aDta);

ReadTarget
ReadFromFile(const str::string& aFullFileName);

ReadTarget
ReadFromFile(const str::string& aFileName, const str::string& aFolderName);

} // namespace fs

//--------------------------------------------------------------------------------
