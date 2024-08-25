#pragma once

//--------------------------------------------------------------------------------

#include <map>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "string/kus_string.hpp"
#include "string/separators.hpp"

#include "read_target.hpp"

//--------------------------------------------------------------------------------

/*
struct DataTarget : public ReadTarget
{
    HOLY_TRINITY_NOCOPY(DataTarget);
    DataTarget(const str::string& aData);
};

struct FilenameRefTarget : public ReadTarget
{
    HOLY_TRINITY_NOCOPY(FilenameRefTarget);
    FilenameRefTarget(const str::string& aData);
};

struct FilenameTarget : public ReadTarget

*/

namespace fs
{

typedef bool (*FPSeparator)(char);

class DataRead
{
public:
    DataRead() noexcept = delete;

    static std::vector<std::string_view> getLines(
        const std::string_view& aData) noexcept;

    static std::vector<std::vector<std::string_view>> getWords(
        const std::string_view& aData,
        FPSeparator aSepFunc = str::Separator::newWord) noexcept;

    static std::unordered_map<std::string_view, std::string_view> getWordsMap(
        const std::string_view& aData,
        FPSeparator aSepFunc = str::Separator::newWord) noexcept;

    static std::unordered_set<std::string_view> getWordsSet(
        const std::string_view& aData,
        FPSeparator aSepFunc = str::Separator::newWord) noexcept;

    static str::string readFile(const str::string& aPath) noexcept;
};

} // namespace fs

//--------------------------------------------------------------------------------
