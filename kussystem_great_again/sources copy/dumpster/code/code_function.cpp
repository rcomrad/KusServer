#include "code_function.hpp"

code::CodeFunction::CodeFunction(const char* aName) noexcept
{
    mIsStatic   = false;
    mIsFunctor  = false;
    mIsVariadic = false;
    mType       = "auto";
    setName(aName);
}

void
code::CodeFunction::setNamespace(const char* aNamespace) noexcept
{
    mNamespace = aNamespace;
}

void
code::CodeFunction::setClass(const char* aClass) noexcept
{
    mClass = aClass;
}

void
code::CodeFunction::makeStatic() noexcept
{
    mIsStatic = true;
}

void
code::CodeFunction::makeFunctor() noexcept
{
    mIsFunctor  = true;
    mIsVariadic = false;
}

void
code::CodeFunction::makeVariadic() noexcept
{
    mIsFunctor  = false;
    mIsVariadic = true;
}

void
code::CodeFunction::setTemplate(const char* aTemplate) noexcept
{
    mTemplate = aTemplate;
}

void
code::CodeFunction::setReturnType(const char* aType) noexcept
{
    mType = aType;
}

void
code::CodeFunction::setName(const char* aName) noexcept
{
    mName = aName;
}

void
code::CodeFunction::setArguments(const char* aArguments) noexcept
{
    mArguments = aArguments;
}

void
code::CodeFunction::setBody(const char* aBody) noexcept
{
    mBody = aBody;
}

void
code::CodeFunction::outputToHpp(std::ofstream& aOut) const noexcept
{
    str::String body = mBody;
    if (!mMapName.empty()) body = generateRouterBody();

    if (mIsVariadic)
    {
        aOut << "template <typename... Args>";
    }
    if (mIsStatic) aOut << "static ";
    aOut << mType << "\n";
    aOut << mName << "(" << mArguments;
    if (mIsVariadic)
    {
        aOut << ", " << "Args&&... args";
    }

    if (isTemplate())
    {
        aOut << ")\n{\n" << body << "}\n\n";
    }
    else
    {
        aOut << ");\n";
    }
}

void
code::CodeFunction::outputToCpp(std::ofstream& aOut) const noexcept
{
    if (!isTemplate())
    {
        aOut << mType << "\n";
        aOut << mNamespace << "::" << mClass << "::" << mName << "("
             << mArguments << ")\n{\n"
             << mBody << "}\n";
    }
}

void
code::CodeFunction::makeRouter(str::String aMapName) noexcept
{
    mArguments = "const char* aName";
    mMapName   = aMapName;
}

str::String
code::CodeFunction::generateRouterBody() const noexcept
{
    str::String execExpr;
    if (mIsFunctor) execExpr = "()";
    if (mIsVariadic) execExpr = "(std::forward<Args>(args)...)";

    return "decltype(" + mMapName + ".begin()->second" + execExpr +
           ") result;\n"
           "auto it = " +
           mMapName +
           ".find(aName);\n"
           "if (it != " +
           mMapName +
           ".end())\n"
           "result= it->second" +
           execExpr +
           ";"
           "return result;\n";
}

bool
code::CodeFunction::isTemplate() const noexcept
{
    return !mTemplate.empty() || mIsVariadic || mType == "auto";
}
