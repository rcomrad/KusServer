#include "code_file.hpp"

#include <fstream>

std::unordered_map<std::string, std::string> code::CodeFile::globalPaths = {
    {"post", "../sources/post/"    },
    {"get",  "../sources/get/"     },
    {"data", "../sources/database/"}
};

// std::unordered_map<std::string, std::string> code::CodeFile::globalPaths = {
//     {"post", ""},
//     {"get",  ""},
//     {"data", ""}
// };

code::CodeFile::CodeFile(const std::string& aClassName,
                         const std::string& aNamespace) noexcept
    : mNamespace(aNamespace)
{
    mFileName = normalizeName(aClassName);
}

code::CodeClass&
code::CodeFile::makeClass(const std::string& aClassName) noexcept
{
    mClasses.emplace_back(
        CodeClass{aClassName.empty() ? mFileName : aClassName, mNamespace});
    mClasses.back().makeStruct();
    return mClasses.back();
}

void
code::CodeFile::generate(CodeFile::FileType aType) const noexcept
{
    std::string CodeFilePath = globalPaths[mNamespace] + mFileName;
    if (int(aType) & int(FileType::CPP)) generateCPP(CodeFilePath);
    if (int(aType) & int(FileType::HEADER)) generateHPP(CodeFilePath);
}

void
code::CodeFile::addHeaderToCpp(const std::string& aName,
                               bool aIsStdHeader) noexcept
{
    mCppHeaders.emplace_back(makeHeader(aName, aIsStdHeader));
}

void
code::CodeFile::addHeaderToHpp(const std::string& aName,
                               bool aIsStdHeader) noexcept
{
    mHppHeaders.emplace_back(makeHeader(aName, aIsStdHeader));
}

void
code::CodeFile::generateCPP(const std::string& aPath) const noexcept
{
    std::ofstream CodeFile(aPath + ".cpp");
    CodeFile << "#include \"" << aPath + ".hpp\"\n\n";
    for (auto& i : mCppHeaders)
    {
        CodeFile << i << "\n";
    }
    CodeFile << "\n";
    for (auto& i : mClasses) i.outputToCpp(CodeFile);
    CodeFile << "\n";
}

void
code::CodeFile::generateHPP(const std::string& aPath) const noexcept
{
    std::ofstream CodeFile(aPath + ".hpp");
    std::string define = normalizeDefine(mFileName) + "_HPP";

    CodeFile << "#ifndef " << define << "\n";
    CodeFile << "#define " << define << "\n\n";

    for (auto& i : mHppHeaders)
    {
        CodeFile << i << "\n";
    }
    CodeFile << "\n";

    {
        CodeFile << "namespace " << mNamespace << "\n";
        CodeFile << "{\n";

        {
            for (auto& i : mClasses)
            {
                i.outputToHpp(CodeFile);
                CodeFile << "\n";
            }
        }

        CodeFile << "};\n";
    }

    CodeFile << "\n#endif "
             << "// !" << define << "\n";
}

std::string
code::CodeFile::normalizeName(const std::string& aName) noexcept
{
    std::string result = aName;

    result[0] = std::tolower(result[0]);
    for (int i = 0; i < result.size(); ++i)
    {
        if (result[i] >= 'A' && result[i] <= 'Z')
        {
            result[i] = std::tolower(result[i]);
            result.insert(result.begin() + i, '_');
        }
    }

    return result;
}

std::string
code::CodeFile::normalizeDefine(const std::string& aName) noexcept
{
    std::string result = aName;

    for (int i = 0; i < result.size(); ++i)
    {
        if (result[i] != '_')
        {
            result[i] = std::toupper(result[i]);
        }
    }

    return result;
}

std::string
code::CodeFile::makeHeader(const std::string& aName, bool aIsStdHeader) noexcept
{
    std::string fullName = "#include ";

    if (aIsStdHeader) fullName.push_back('<');
    else fullName.push_back('\"');

    fullName += aName;

    if (aIsStdHeader) fullName.push_back('>');
    else fullName += ".hpp\"";

    return fullName;
}
