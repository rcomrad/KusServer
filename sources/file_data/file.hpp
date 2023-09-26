#ifndef KUS_FILE_HPP
#define KUS_FILE_HPP

//--------------------------------------------------------------------------------

#include <array>
#include <functional>
#include <map>
#include <optional>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "domain/log.hpp"

#include "path.hpp"

//--------------------------------------------------------------------------------

namespace file
{

// To avoid an implicit conversion from const char* to bool
enum class Critical
{
    Yes,
    No
};

class File
{
public:
    File() noexcept = delete;

    static std::string getAllData(const std::string& aFileName,
                                  Critical aIsCritical = Critical::No) noexcept;
    static std::string getAllData(const std::string& aFolderName,
                                  const std::string& aFileName,
                                  Critical aIsCritical = Critical::No) noexcept;

    static std::vector<std::string> getLines(
        const std::string& aFileName,
        Critical aIsCritical = Critical::No) noexcept;
    static std::vector<std::string> getLines(
        const std::string& aFolderName,
        const std::string& aFileName,
        Critical aIsCritical = Critical::No) noexcept;

    static std::vector<std::vector<std::string>> getWords(
        const std::string& aFileName,
        Critical aIsCritical           = Critical::No,
        std::function<bool(char)> funk = &file::File::isSeparator) noexcept;
    static std::vector<std::vector<std::string>> getWords(
        const std::string& aFolderName,
        const std::string& aFileName,
        Critical aIsCritical           = Critical::No,
        std::function<bool(char)> funk = &file::File::isSeparator) noexcept;

    static std::unordered_map<std::string, std::string> getWordsMap(
        const std::string& aFileName,
        Critical aIsCritical           = Critical::No,
        std::function<bool(char)> funk = &file::File::isSeparator) noexcept;
    static std::unordered_map<std::string, std::string> getWordsMap(
        const std::string& aFolderName,
        const std::string& aFileName,
        Critical aIsCritical           = Critical::No,
        std::function<bool(char)> funk = &file::File::isSeparator) noexcept;

    static std::unordered_set<std::string> getWordsSet(
        const std::string& aFileName,
        Critical aIsCritical           = Critical::No,
        std::function<bool(char)> funk = &file::File::isSeparator) noexcept;
    static std::unordered_set<std::string> getWordsSet(
        const std::string& aFolderName,
        const std::string& aFileName,
        Critical aIsCritical           = Critical::No,
        std::function<bool(char)> funk = &file::File::isSeparator) noexcept;

    static bool writeData(const std::string& aFileName,
                          const std::string& aData) noexcept;
    static std::optional<std::string> writeData(
        const std::string& aFolderName,
        const std::string& aFileName,
        const std::string& aData) noexcept;

private:
    static bool isSeparator(char c) noexcept;

    template <typename T, typename... Args>
    static auto pathUnpack(T aFuncPtr,
                           const std::string& aFolderName,
                           const std::string& aFileName,
                           Args&&... args) noexcept
    {
        auto path = file::Path::getPath(aFolderName, aFileName);
        decltype(aFuncPtr(path.value(), std::forward<Args>(args)...)) result;
        if (path.has_value())
        {
            result = aFuncPtr(path.value(), std::forward<Args>(args)...);
        }
        else
        {
            dom::writeError("No such file ( Folder:", aFolderName,
                            ", Name:", aFileName, ")");
        }
        return result;
    }
};

} // namespace file

//--------------------------------------------------------------------------------

#endif // !KUS_FILE_HPP
