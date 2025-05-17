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
enum class FileType
{
    File,
    String
};

class File
{
public:
    File() noexcept = delete;

    // TODO: add tamplate (factory, for file read and string read)
    static str::String getAllData(const char* aFileName,
                                  FileType aFileType = FileType::File) noexcept;
    static str::String getAllData(const char* aFolderName,
                                  const char* aFileName,
                                  FileType aFileType = FileType::File) noexcept;

    static std::vector<str::String> getLines(
        const char* aFileName,
        FileType aFileType = FileType::File) noexcept;
    static std::vector<str::String> getLines(
        const char* aFolderName,
        const char* aFileName,
        FileType aFileType = FileType::File) noexcept;

    static std::vector<std::vector<str::String>> getWords(
        const char* aFileName,
        FileType aFileType             = FileType::File,
        std::function<bool(char)> funk = &file::File::isSeparator) noexcept;
    static std::vector<std::vector<str::String>> getWords(
        const char* aFolderName,
        const char* aFileName,
        FileType aFileType             = FileType::File,
        std::function<bool(char)> funk = &file::File::isSeparator) noexcept;

    static std::unordered_map<str::String, str::String> getWordsMap(
        const char* aFileName,
        FileType aFileType             = FileType::File,
        std::function<bool(char)> funk = &file::File::isSeparator) noexcept;
    static std::unordered_map<str::String, str::String> getWordsMap(
        const char* aFolderName,
        const char* aFileName,
        FileType aFileType             = FileType::File,
        std::function<bool(char)> funk = &file::File::isSeparator) noexcept;

    static std::unordered_set<str::String> getWordsSet(
        const char* aFileName,
        FileType aFileType             = FileType::File,
        std::function<bool(char)> funk = &file::File::isSeparator) noexcept;
    static std::unordered_set<str::String> getWordsSet(
        const char* aFolderName,
        const char* aFileName,
        FileType aFileType             = FileType::File,
        std::function<bool(char)> funk = &file::File::isSeparator) noexcept;

    static std::vector<std::unordered_map<str::String, str::String>> getTable(
        const char* aFileName,
        FileType aFileType             = FileType::File,
        std::function<bool(char)> funk = &file::File::isSeparator) noexcept;
    static std::vector<std::unordered_map<str::String, str::String>> getTable(
        const char* aFolderName,
        const char* aFileName,
        FileType aFileType             = FileType::File,
        std::function<bool(char)> funk = &file::File::isSeparator) noexcept;

    static bool writeData(const char* aFileName, const char* aData) noexcept;
    static std::optional<str::String> writeData(const char* aFolderName,
                                                const char* aFileName,
                                                const char* aData) noexcept;

private:
    static bool isSeparator(char c) noexcept;

    template <typename T, typename... Args>
    static auto pathUnpack(T aFuncPtr,
                           const char* aFolderName,
                           const char* aFileName,
                           Args&&... args) noexcept
    {
        auto path = core::Path::getPath(aFolderName, aFileName);
        decltype(aFuncPtr(path.value(), std::forward<Args>(args)...)) result;
        if (path.has_value())
        {
            result = aFuncPtr(path.value(), std::forward<Args>(args)...);
        }
        else
        {
            LOG_ERROR("Can't find such file ( Folder:", aFolderName,
                      ", Name:", aFileName, ")");
        }
        return result;
    }
};

} // namespace file

//--------------------------------------------------------------------------------

#endif // !KUS_FILE_HPP
