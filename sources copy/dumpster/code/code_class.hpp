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
    CodeClass(const str::String& aClassName,
              const str::String& aNamespace) noexcept;
    // void setName(const str::String& aName) noexcept;
    // void setNamespace(const str::String& aNamespace) noexcept;

    void addParent(const str::String& aName) noexcept;

    CodeFunction& addRouterFunction(const str::String& aName,
                                    const str::String& aType,
                                    const str::String& aBody) noexcept;
    CodeFunction& addFuncRouterForDatabase(const str::String& aName,
                                           const str::String& aFunction,
                                           const str::String& aBody) noexcept;

    void addFunction(const CodeFunction& aFunc) noexcept;

    void addVariable(const str::String& aName,
                     const str::String& aType,
                     const str::String& aValue = "") noexcept;
    void addStaticVariable(const str::String& aVarName,
                           const str::String& aType,
                           const str::String& aInitialisation) noexcept;

    void outputToCpp(std::ofstream& aFile) const noexcept;
    void outputToHpp(std::ofstream& aFile) const noexcept;

    void makeStruct() noexcept;
    void addUsing(const str::String& aName,
                  const str::String& aTemplate = "") noexcept;

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
