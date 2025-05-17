#ifndef CODE_CLASS_HPP
#define CODE_CLASS_HPP

#include <array>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "code_function.hpp"
#include "static_variable.hpp"

namespace code
{

class CodeClass
{
public:
    CodeClass(const std::string& aClassName,
              const std::string& aNamespace) noexcept;
    // void setName(const std::string& aName) noexcept;
    // void setNamespace(const std::string& aNamespace) noexcept;

    void addParent(const std::string& aName) noexcept;

    CodeFunction& addRouterFunction(const std::string& aName,
                                    const std::string& aType,
                                    const std::string& aBody) noexcept;
    CodeFunction& addFuncRouterForDatabase(const std::string& aName,
                                           const std::string& aFunction,
                                           const std::string& aBody) noexcept;

    void addFunction(const CodeFunction& aFunc) noexcept;

    void addVariable(const std::string& aName,
                     const std::string& aType,
                     const std::string& aValue = "") noexcept;
    void addStaticVariable(const std::string& aVarName,
                           const std::string& aType,
                           const std::string& aInitialisation) noexcept;

    void outputToCpp(std::ofstream& aFile) const noexcept;
    void outputToHpp(std::ofstream& aFile) const noexcept;

    void makeStruct() noexcept;
    void addUsing(const std::string& aName,
                  const std::string& aTemplate = "") noexcept;

private:
    bool mIsStruct;
    std::string mParent;
    std::string mUsing;

    std::string mClassName;
    std::string mNamespace;

    std::vector<CodeFunction> mFunctions;
    std::vector<StaticVariable> mStaticVariables;
    std::vector<std::array<std::string, 3>> mSimpleVariables;

    std::vector<std::string> mDatabase;

    // void reloadName() noexcept;
};

} // namespace code

#endif // !CODE_CLASS_HPP
