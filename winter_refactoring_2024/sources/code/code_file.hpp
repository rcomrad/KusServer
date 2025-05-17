#ifndef CODE_FILE_HPP
#define CODE_FILE_HPP

#include "code_class.hpp"

namespace code
{
class CodeFile
{
public:
    enum class FileType
    {
        NUN    = 0,
        HEADER = 1,
        CPP    = 2,
        ALL    = 3
    };

    CodeFile(const std::string& aClassName, const std::string& aNamespace) noexcept;
    CodeClass& makeClass(const std::string& aClassName = "") noexcept;
    void generate(FileType aType) const noexcept;

    void addHeaderToCpp(const std::string& aName, bool aIsStdHeader) noexcept;
    void addHeaderToHpp(const std::string& aName, bool aIsStdHeader) noexcept;

private:
    static std::unordered_map<std::string, std::string> globalPaths;

    std::string mNamespace;
    std::string mFileName;
    std::string mFilePath;

    std::vector<std::string> mCppHeaders;
    std::vector<std::string> mHppHeaders;

    std::vector<CodeClass> mClasses;

    void generateCPP(const std::string& aPath) const noexcept;
    void generateHPP(const std::string& aPath) const noexcept;

    static std::string normalizeName(const std::string& aName) noexcept;
    static std::string normalizeDefine(const std::string& aName) noexcept;

    static std::string makeHeader(const std::string& aName,
                                  bool aIsStdHeader) noexcept;
};

} // namespace code

#endif // !CODE_FILE_HPP
