#pragma once

//--------------------------------------------------------------------------------

#include <map>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "string/separators.hpp"

#include "read_target.hpp"

//--------------------------------------------------------------------------------

/*
struct DataTarget : public ReadTarget
{
    HOLY_TRINITY_NOCOPY(DataTarget);
    DataTarget(const char* aData);
};

struct FilenameRefTarget : public ReadTarget
{
    HOLY_TRINITY_NOCOPY(FilenameRefTarget);
    FilenameRefTarget(const char* aData);
};

struct FilenameTarget : public ReadTarget

*/

namespace fs
{

typedef bool (*FPSeparator)(char);

class FileRead
{
public:
    FileRead() noexcept = delete;

    static const char* getData(const DataTarget& aTarget) noexcept;
    static str::String getData(const FilenameRefTarget& aTarget) noexcept;

    static std::vector<str::String> getLines(
        const ReadTarget& aTarget) noexcept;

    static std::vector<std::vector<str::String>> getWords(
        const ReadTarget& aTarget,
        FPSeparator aSepFunc = str::Separator::newWord) noexcept;

    static std::unordered_map<str::String, str::String> getWordsMap(
        const ReadTarget& aTarget,
        FPSeparator aSepFunc = str::Separator::newWord) noexcept;

    static std::unordered_set<str::String> getWordsSet(
        const ReadTarget& aTarget,
        FPSeparator aSepFunc = str::Separator::newWord) noexcept;
};

} // namespace fs

//--------------------------------------------------------------------------------
