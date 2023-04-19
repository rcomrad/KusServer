#ifndef KUS_FILE_HPP
#define KUS_FILE_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>
#include <vector>

#include "file_data.hpp"

//--------------------------------------------------------------------------------

namespace file
{

class File
{
public:
    static FileData dmpParser(const std::string& aFileName) noexcept;

    static std::string getAllData(const std::string& aFileName) noexcept;
    static std::vector<std::string> getLines(
        const std::string& aFileName) noexcept;
    static std::vector<std::vector<std::string>> getWords(
        const std::string& aFileName) noexcept;

    static std::string getAllWithBr(const std::string& aFileName) noexcept;

    static std::string writeData(const std::string& aFolderName,
                                 const std::string& aFileName,
                                 const std::string& aData) noexcept;

private:
    static bool isSeparator(char c) noexcept;
};

} // namespace file

//--------------------------------------------------------------------------------

#endif // !KUS_FILE_HPP
