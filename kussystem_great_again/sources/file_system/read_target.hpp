#pragma once

//--------------------------------------------------------------------------------

#include "core/holy_trinity.hpp"

#include "string/kus_string.hpp"

//--------------------------------------------------------------------------------

namespace fs
{

struct ReadTarget
{
    HOLY_TRINITY_NOCOPY(ReadTarget);

    enum Type
    {
        NUN,
        DATA,
        FILE_NAME,
        FILE_NAME_REF
    };

    Type mType;
    const char* mData;

    ReadTarget(Type aType, const char* aData);
};

//--------------------------------------------------------------------------------

struct DataTarget : public ReadTarget
{
    HOLY_TRINITY_NOCOPY(DataTarget);
    DataTarget(const char* aData);
};

struct FilenameRefTarget : public ReadTarget
{
    HOLY_TRINITY_NOCOPY(FilenameRefTarget);
    FilenameRefTarget(const char* aData, Type aType);
};

struct FilenameTarget : public ReadTarget
{
    str::String mFilename;

    HOLY_TRINITY_NOCOPY(FilenameTarget);
    FilenameTarget(char*& aData, Type aType);
};

//--------------------------------------------------------------------------------

DataTarget
ReadFromData(const char* aData);

FilenameRefTarget
ReadFromFilePath(const char* aFullFileName);

FilenameRefTarget
ReadFromStoredFile(const char* aFileName);

FilenameTarget
ReadFromStoredFile(const char* aFolderName, const char* aFileName);

} // namespace fs

//--------------------------------------------------------------------------------
