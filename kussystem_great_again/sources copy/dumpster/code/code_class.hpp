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
    CodeClass(const char* aClassName, const char* aNamespace) noexcept;
    // void setName(const char* aName) noexcept;
    // void setNamespace(const char* aNamespace) noexcept;

    void addParent(const char* aName) noexcept;

    CodeFunction& addRouterFunction(const char* aName,
                                    const char* aType,
                                    const char* aBody) noexcept;
    CodeFunction& addFuncRouterForDatabase(const char* aName,
                                           const char* aFunction,
                                           const char* aBody) noexcept;

    void addFunction(const CodeFunction& aFunc) noexcept;

    void addVariable(const char* aName,
                     const char* aType,
                     const char* aValue = "") noexcept;
    void addStaticVariable(const char* aVarName,
                           const char* aType,
                           const char* aInitialisation) noexcept;

    void outputToCpp(std::ofstream& aFile) const noexcept;
    void outputToHpp(std::ofstream& aFile) const noexcept;

    void makeStruct() noexcept;
    void addUsing(const char* aName, const char* aTemplate = "") noexcept;

private:
    bool mIsStruct;
    str::String mParent;
    str::String mUsing;

    str::String mClassName;
    str::String mNamespace;

    std::vector<CodeFunction> mFunctions;
    std::vector<StaticVariable> mStaticVariables;
    std::vector<std::array<str::String, 3>> mSimpleVariables;

    std::vector<str::String> mDatabase;

    // void reloadName() noexcept;
};

} // namespace code

#endif // !CODE_CLASS_HPP
