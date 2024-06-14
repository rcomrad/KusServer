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

    CodeFile(const str::String& aClassName,
             const str::String& aNamespace) noexcept;
    CodeClass& makeClass(const str::String& aClassName = "") noexcept;
    void generate(FileType aType) const noexcept;

    void addHeaderToCpp(const str::String& aName, bool aIsStdHeader) noexcept;
    void addHeaderToHpp(const str::String& aName, bool aIsStdHeader) noexcept;

private:
    static std::unordered_map<str::String, str::String> globalPaths;

    str::String mNamespace;
    str::String mFileName;
    str::String mFilePath;

    std::vector<str::String> mCppHeaders;
    std::vector<str::String> mHppHeaders;

    std::vector<CodeClass> mClasses;

    void generateCPP(const str::String& aPath) const noexcept;
    void generateHPP(const str::String& aPath) const noexcept;

    static str::String normalizeName(const str::String& aName) noexcept;
    static str::String normalizeDefine(const str::String& aName) noexcept;

    static str::String makeHeader(const str::String& aName,
                                  bool aIsStdHeader) noexcept;
};

} // namespace code

#endif // !CODE_FILE_HPP
