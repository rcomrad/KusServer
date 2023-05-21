#ifndef GENERATE_CODE_HPP
#define GENERATE_CODE_HPP

#include <fstream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace code
{
class GenerateCode
{
public:
    GenerateCode() noexcept;

    void generateAllFiles() noexcept;

    void generateDatabaseStructureFiles() noexcept;
    void generateDatabaseStructuresHPPFile() noexcept;
    void generateDatabaseStructuresCPPFile() noexcept;

    void generatePostHandlerFile() noexcept;
    void generateGetRouterFile() noexcept;

private:
    std::unordered_map<std::string, std::string> mPaths;

    struct Table
    {
        std::string name;
        std::string className;
        std::vector<std::string> fields;
    };
    std::vector<Table> mTables;

    void getTableData() noexcept;

    void setClassName(const std::string& aName);
    void setNamespace(const std::string& aName);

    void setDefaultTemplate(const std::string& aDefaultTemplate);
    void setDefaultReturnType(const std::string& aDefaultReturnType);
    void setDefaultResult(const std::string& aBegin, const std::string& aEnd);
    void setDefaultResultBegin(const std::string& aDefaultResultBegin);
    void setDefaultResultEnd(const std::string& aDefaultResultEnd);

    void addInclude(const std::string& aInclude, bool aIsSTD = false);
    void addCPPInclude(const std::string& aInclude, bool aIsSTD = false);
    // void addFunction(const std::string& aTemplate,
    //                  const std::string& aReturnType,
    //                  const std::string& aSignature, const std::string&
    //                  aBody);

    void pushBackFunction(const std::string& aSignature);
    void pushToFunctionBody(const std::string& aBody);
    void generateElseIfTable(
        const std::unordered_map<std::string, std::string>& aGotoTable = {});

    void generateMapTable(
        const std::string& aName,
        const std::unordered_map<std::string, std::string>& aGotoTable = {},
        bool aAddTemplate                                              = false);

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

        std::string getDeclaration()
        {
            std::string result = _template + "\n";
            result += returnType + "\n";
            result += signature;

            if (_template.empty()) result += ";\n";
            else
            {
                result += "\n{\n";
                if (!resultBegin.empty())
                {
                    result += resultBegin;
                    result += "\n\n";
                }
                result += body;
                if (!resultEnd.empty())
                {
                    result += "\n\n";
                    result += resultEnd;
                }
                result += "\n}\n\n";
            }

            return result;
        }

        std::string getInitialisation(const std::string& aNamespace,
                                      const std::string& aClassName)
        {
            std::string result;

            if (_template.empty())
            {
                result += returnType + "\n";
                result += aNamespace + "::" + aClassName + "::";
                result += signature;
                result += "\n{\n";
                result += resultBegin;
                result += "\n\n";
                result += body;
                result += "\n\n";
                result += resultEnd;
                result += "\n}\n\n";
            }

            return result;
        }
    };

    struct StaticVar
    {
        std::string type;
        std::string name;
        std::string initialisation;

        std::string getDeclaration()
        {
            return "static " + type + name + ";";
        }

        std::string getInitialisation(const std::string& aNamespace,
                                      const std::string& aClassName)
        {
            return type + " " + aNamespace + "::" + aClassName + "::" + name +
                   " = " + initialisation;
        }
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

    std::set<std::string> mIncludes;
    std::set<std::string> mCPPIncludes;
    std::vector<Function> mFunctions;
    std::vector<StaticVar> mStaticVariables;

    static std::unordered_map<std::string, std::string> mglobalPaths;
    static std::vector<std::string> mDatabaseTables;

    static std::vector<std::string> getDatabaseTables();
};

void
generateDatabaseStructuresFiles();

} // namespace code

#endif // !GENERATE_CODE_HPP
