#include "code_class.hpp"

#include "string_algorithms.hpp"

// void
// code::CodeClass::setName(const char* aName) noexcept
// {
//     mName = normalizeName(aName, true);

//     reloadName();
// }

// void
// code::CodeClass::setNamespace(const char* aNamespace) noexcept
// {
//     mNamespace = aNamespace;
//     reloadName();
// }

code::CodeClass::CodeClass(const char* aCodeClassName,
                           const char* aNamespace) noexcept
    : mIsStruct(false), mNamespace(aNamespace)
{
    mClassName = StringAlgorithms::normalizeName(aCodeClassName, true);
}

void
code::CodeClass::addParent(const char* aName) noexcept
{
    mParent = aName;
}

code::CodeFunction&
code::CodeClass::addRouterFunction(const char* aName,
                                   const char* aType,
                                   const char* aBody) noexcept
{
    str::String variableName = "m" + aName;
    variableName[1]          = std::toupper(variableName[1]);

    auto& funk = mFunctions.emplace_back();
    funk.makeStatic();
    funk.setName(aName);
    funk.setClass(mClassName);
    funk.setNamespace(mNamespace);
    funk.setArguments("str::String aName");
    funk.makeRouter(variableName);

    addStaticVariable(variableName,
                      "std::unordered_map<str::String, " + aType + ">", aBody);

    return funk;
}

code::CodeFunction&
code::CodeClass::addFuncRouterForDatabase(const char* aName,
                                          const char* aFunction,
                                          const char* aBody) noexcept
{
    auto& funk = addRouterFunction(aName, "decltype(" + aFunction + ")", aBody);
    funk.makeVariadic();
    return funk;
}

void
code::CodeClass::addFunction(const CodeFunction& aFunc) noexcept
{
    CodeFunction func = aFunc;
    func.setNamespace(mNamespace);
    func.setClass(mClassName);
    mFunctions.emplace_back(func);
};

void
code::CodeClass::addVariable(const char* aName,
                             const char* aType,
                             const char* aValue) noexcept
{
    str::String name = StringAlgorithms::normalizeName(aName, false, true);
    mSimpleVariables.push_back({name, aType, aValue});
};

void
code::CodeClass::addStaticVariable(const char* aVarName,
                                   const char* aType,
                                   const char* aInitialisation) noexcept
{
    mStaticVariables.emplace_back();
    auto& var = mStaticVariables.back();
    var.setClass(mClassName);
    var.setNamespace(mNamespace);
    var.setName(aVarName);
    var.setType(aType);
    var.setInitialisation(aInitialisation);
}

void
code::CodeClass::outputToCpp(std::ofstream& aFile) const noexcept
{
    for (auto& i : mStaticVariables)
    {
        i.outputToCpp(aFile);
    }

    aFile << "\n";

    for (auto& i : mFunctions)
    {
        i.outputToCpp(aFile);
        aFile << "\n";
    }
}

void
code::CodeClass::outputToHpp(std::ofstream& aFile) const noexcept
{
    if (mIsStruct) aFile << "struct " << mClassName;
    else aFile << "CodeClass " << mClassName;

    if (!mParent.empty()) aFile << " : public " << mParent;
    aFile << "\n{\n";

    {
        // aFile << "public:\n";

        for (auto& i : mSimpleVariables)
        {
            aFile << i[1] << " " << i[0];
            if (!i[2].empty())
            {
                aFile << "=" << i[2];
            }
            aFile << ";\n";
        }
        aFile << "\n";

        for (auto& i : mStaticVariables)
        {
            i.outputToHpp(aFile);
        }
        aFile << "\n";

        for (auto& i : mFunctions)
        {
            i.outputToHpp(aFile);
        }
        aFile << "\n";
    }
    aFile << "};\n";
    if (!mUsing.empty())
    {
        aFile << "\n" << mUsing << "\n";
    }
}

void
code::CodeClass::makeStruct() noexcept
{
    mIsStruct = true;
}

void
code::CodeClass::addUsing(const char* aName, const char* aTemplate) noexcept
{
    mUsing = "using " + StringAlgorithms::normalizeName(aName, true) + " = ";
    if (!aTemplate.empty()) mUsing += aTemplate + "<";
    mUsing += mClassName;
    if (!aTemplate.empty()) mUsing += ">";
    mUsing += ";";
}

// void
// code::CodeClass::reloadName() noexcept
// {
//     mFilePath = globalPaths[mNamespace] + mFileName;
// }
