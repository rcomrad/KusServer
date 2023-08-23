#ifndef KUS_FILE_HPP
#define KUS_FILE_HPP

//--------------------------------------------------------------------------------

#include <array>
#include <functional>
#include <map>
#include <optional>
#include <string>
#include <unordered_set>
#include <vector>

//--------------------------------------------------------------------------------

namespace file
{

class File
{
public:
    File() noexcept = delete;

    static std::string getAllData(const std::string& aFileName,
                                  bool aIsCritical = false) noexcept;
    static std::vector<std::string> getLines(const std::string& aFileName,
                                             bool aIsCritical = false) noexcept;
    static std::vector<std::vector<std::string>> getWords(
        const std::string& aFileName,
        bool aIsCritical               = false,
        std::function<bool(char)> funk = &file::File::isSeparator) noexcept;

    static std::unordered_map<std::string, std::string> getWordsMap(
        const std::string& aFileName,
        bool aIsCritical               = false,
        std::function<bool(char)> funk = &file::File::isSeparator) noexcept;

    static std::unordered_set<std::string> getWordsSet(
        const std::string& aFileName,
        bool aIsCritical               = false,
        std::function<bool(char)> funk = &file::File::isSeparator) noexcept;

    static bool writeData(const std::string& aFileName,
                          const std::string& aData) noexcept;
    static std::optional<std::string> writeData(
        const std::string& aFolderName,
        const std::string& aFileName,
        const std::string& aData) noexcept;

private:
    static bool isSeparator(char c) noexcept;
};

} // namespace file

//--------------------------------------------------------------------------------

#endif // !KUS_FILE_HPP
