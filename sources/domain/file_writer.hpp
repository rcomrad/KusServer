#ifndef FILES_WRITER_HPP
#define FILES_WRITER_HPP

//--------------------------------------------------------------------------------

#include <fstream>
#include <string>

//--------------------------------------------------------------------------------

namespace dom
{
class FileWrite
{
public:
    FileWrite(const std::string& aFileName) noexcept;
    ~FileWrite();

    FileWrite(const FileWrite& other)            = delete;
    FileWrite& operator=(const FileWrite& other) = delete;

    FileWrite(FileWrite&& other) noexcept            = default;
    FileWrite& operator=(FileWrite&& other) noexcept = default;

    template <typename... Args> void write(Args... args) noexcept
    {
        (void)std::initializer_list<bool>{
            static_cast<bool>(mOut << args << mDelimiter)...};
        mOut << '\n';
    }

    void setDelimiter(const std::string& aDelimiter) noexcept;
    void writeEndl() noexcept;

    void close() noexcept;

    static void copyFile(const std::string& aFromFileName,
                         const std::string& aToFileName) noexcept;

private:
    std::ofstream mOut;
    std::string mDelimiter;
};
} // namespace dom

//--------------------------------------------------------------------------------

#endif // !FILES_WRITER_HPP
