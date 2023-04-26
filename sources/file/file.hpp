#ifndef KUS_FILE_HPP
#define KUS_FILE_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>
#include <vector>

//--------------------------------------------------------------------------------

namespace file
{

struct FileData
{
    std::vector<std::vector<std::string>> value;
    std::vector<std::vector<std::string>> additionalInfo;
};
using FileDataArray = std::unordered_map<std::string, FileData>;

class File
{
public:
    static FileDataArray dmpParser(const std::string& aFileName) noexcept;
    static FileDataArray dataParser(const std::string& aFileName) noexcept;

    static std::string getAllData(const std::string& aFileName) noexcept;
    static std::vector<std::string> getLines(
        const std::string& aFileName) noexcept;
    static std::vector<std::vector<std::string>> getWords(
        const std::string& aFileName) noexcept;

    static std::string writeData(const std::string& aFolderName,
                                 const std::string& aFileName,
                                 const std::string& aData) noexcept;

private:
    static bool isSeparator(char c) noexcept;
};

} // namespace file

//--------------------------------------------------------------------------------

#endif // !KUS_FILE_HPP
