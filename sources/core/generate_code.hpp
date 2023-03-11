#ifndef GENERATE_CODE_HPP
#define GENERATE_CODE_HPP

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace core
{
class GenerateCode
{
public:
    void setClassName(const std::string& aName);
    void setNamespace(const std::string& aName);

    void setDefaultTemplate(const std::string& aDefaultTemplate);
    void setDefaultReturnType(const std::string& aDefaultReturnType);
    void setDefaultResult(const std::string& aBegin, const std::string& aEnd);
    void setDefaultResultBegin(const std::string& aDefaultResultBegin);
    void setDefaultResultEnd(const std::string& aDefaultResultEnd);

    void addInclude(const std::string& aInclude);
    // void addFunction(const std::string& aTemplate,
    //                  const std::string& aReturnType,
    //                  const std::string& aSignature, const std::string&
    //                  aBody);

    void pushBackFunction(const std::string& aSignature);
    // void addFunctionBody();
    void generateTableSwitcher(
        const std::unordered_map<std::string, std::string>& aGotoTable = {});

    void write();
    void writeHPP();
    void writeCPP();

private:
    struct Function
    {
        std::string _template;
        std::string returnType;
        std::string signature;
        std::string resultBegin;
        std::string body;
        std::string resultEnd;
    };

    std::string mFileName;
    std::string mClassName;
    std::string mNamespace;
    std::string mDefineName;
    std::string mPath;

    std::string mDefaultTemplate;
    std::string mDefaultReturnType;
    std::string mDefaultResultBegin;
    std::string mDefaultResultEnd;

    std::vector<std::string> mIncludes;
    std::vector<Function> mFunctions;

    static std::unordered_map<std::string, std::string> mglobalPaths;
    static std::vector<std::string> mDatabaseTables;

    static std::vector<std::string> getDatabaseTables();
};

void
generateDatabaseStructuresFiles();

} // namespace data

#endif // !GENERATE_CODE_HPP
