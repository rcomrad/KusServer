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

    CodeFile(const char* aClassName, const char* aNamespace) noexcept;
    CodeClass& makeClass(const char* aClassName = "") noexcept;
    void generate(FileType aType) const noexcept;

    void addHeaderToCpp(const char* aName, bool aIsStdHeader) noexcept;
    void addHeaderToHpp(const char* aName, bool aIsStdHeader) noexcept;

private:
    static std::unordered_map<str::String, str::String> globalPaths;

    str::String mNamespace;
    str::String mFileName;
    str::String mFilePath;

    std::vector<str::String> mCppHeaders;
    std::vector<str::String> mHppHeaders;

    std::vector<CodeClass> mClasses;

    void generateCPP(const char* aPath) const noexcept;
    void generateHPP(const char* aPath) const noexcept;

    static str::String normalizeName(const char* aName) noexcept;
    static str::String normalizeDefine(const char* aName) noexcept;

    static str::String makeHeader(const char* aName,
                                  bool aIsStdHeader) noexcept;
};

} // namespace code

#endif // !CODE_FILE_HPP
