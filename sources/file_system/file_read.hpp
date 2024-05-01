#pragma once

//--------------------------------------------------------------------------------

#include <map>
#include <optional>
#include <unordered_set>

#include "string/kus_string.hpp"

#include "read_result.hpp"
#include "read_target.hpp"

//--------------------------------------------------------------------------------

namespace fs
{

typedef bool (*FPSeparator)(char);

class FileRead
{
public:
    FileRead() noexcept = delete;

    static ReadResult getData(const ReadTarget& aTarget) noexcept;

    static std::vector<str::string> getLines(
        const ReadTarget& aTarget) noexcept;

    static std::vector<str::string> getWords(const ReadTarget& aTarget,
                                             FPSeparator aSepFunc) noexcept;
    static std::vector<str::string> getWordsMap(const ReadTarget& aTarget,
                                                FPSeparator aSepFunc) noexcept;
    static std::vector<str::string> getWordsSet(const ReadTarget& aTarget,
                                                FPSeparator aSepFunc) noexcept;

private:
    static str::string readFile(const str::string& aPath) noexcept;
};

} // namespace fs

//--------------------------------------------------------------------------------
