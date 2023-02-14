#ifndef FILES_READER_HPP
#define FILES_READER_HPP

//--------------------------------------------------------------------------------

#include <fstream>
#include <string>
#include <vector>

//--------------------------------------------------------------------------------

namespace dom
{
class FileReader
{
public:
    FileReader(const std::string& aFileName) noexcept;
    ~FileReader();

    FileReader(const FileReader& other)            = delete;
    FileReader& operator=(const FileReader& other) = delete;

    FileReader(FileReader&& other) noexcept            = default;
    FileReader& operator=(FileReader&& other) noexcept = default;

    static std::vector<std::string> getAllStrings(
        const std::string& aFileName) noexcept;

    void close() noexcept;

private:
    std::ifstream mInp;
};
} // namespace dom

//--------------------------------------------------------------------------------

#endif // !FILES_READER_HPP
