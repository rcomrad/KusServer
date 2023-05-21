#include "function_array.hpp"

code::FunctionArray::FunctionArray() noexcept
{
    setDefaultReturnType("auto");
}

void
code::FunctionArray::setNamespace(const std::string& aName)
{
    mNamespace = aName;
}

void
code::FunctionArray::setDefaultTemplate(const std::string& aDefaultTemplate)
{
    mDefaultTemplate = aDefaultTemplate;
}

void
code::FunctionArray::setDefaultReturnType(const std::string& aDefaultReturnType)
{
    mDefaultReturnType = aDefaultReturnType;
}

void
code::FunctionArray::setDefaultResultBegin(
    const std::string& aDefaultResultBegin)
{
    mDefaultResultBegin = aDefaultResultBegin;
}

void
code::FunctionArray::setDefaultResultEnd(const std::string& aDefaultResultEnd)
{
    mDefaultResultEnd = aDefaultResultEnd;
}

void
code::FunctionArray::addInclude(const std::string& aInclude, bool aIsSTD)
{
    if (aIsSTD) mIncludes.insert("<" + aInclude + ">\n");
    else mIncludes.insert("\"" + aInclude + ".hpp\"\n");
}

void
code::FunctionArray::addCPPInclude(const std::string& aInclude, bool aIsSTD)
{
    if (aIsSTD) mCPPIncludes.insert("<" + aInclude + ">\n");
    else mCPPIncludes.insert("\"" + aInclude + ".hpp\"\n");
}

// void
// code::FunctionArray::addFunction(const std::string& aTemplate,
//                                 const std::string& aReturnType,
//                                 const std::string& aSignature,
//                                 const std::string& aBody)
// {
//     const std::string* templ = &aTemplate;
//     if (aTemplate.empty())
//     {
//         templ = &mDefaultTemplate;
//     }

//     const std::string* retur = &aReturnType;
//     if (aReturnType.empty())
//     {
//         retur = &mDefaultReturnType;
//     }

//     mFunctions.emplace_back(
//         std::vector<std::string>{*templ, *retur, aSignature, aBody});
// }

void
code::FunctionArray::pushBackFunction(const std::string& aSignature)
{
    mFunctions.emplace_back();

    mFunctions.back()._template   = mDefaultTemplate;
    mFunctions.back().returnType  = mDefaultReturnType;
    mFunctions.back().signature   = aSignature;
    mFunctions.back().resultBegin = mDefaultResultBegin;
    mFunctions.back().resultEnd   = mDefaultResultEnd;
}


std::string
wrap(std::string aname)
{
    return "crow::json::wvalue result;\n"
           "auto it = " +
           aname +
           ".find(aTableName);\n"
           "if (it != " +
           aname +
           ".end())\n"
           "result= it->second(args...);return result;\n";
}

std::string
wrap2(std::string aname)
{
    return "decltype(" + aname +
           ".begin()->second) result;\n"
           "auto it = " +
           aname +
           ".find(aTableName);\n"
           "if (it != " +
           aname +
           ".end())\n"
           "auto result= it->second;"
           "return result;\n";
}
