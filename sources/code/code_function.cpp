#include "code_function.hpp"

code::CodeFunction::CodeFunction(const std::string& aName) noexcept
{
    mIsStatic   = false;
    mIsFunctor  = false;
    mIsVariadic = false;
    mType       = "auto";
    setName(aName);
}

void
code::CodeFunction::setNamespace(const std::string& aNamespace) noexcept
{
    mNamespace = aNamespace;
}

void
code::CodeFunction::setClass(const std::string& aClass) noexcept
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
code::CodeFunction::setTemplate(const std::string& aTemplate) noexcept
{
    mTemplate = aTemplate;
}

void
code::CodeFunction::setReturnType(const std::string& aType) noexcept
{
    mType = aType;
}

void
code::CodeFunction::setName(const std::string& aName) noexcept
{
    mName = aName;
}

void
code::CodeFunction::setArguments(const std::string& aArguments) noexcept
{
    mArguments = aArguments;
}

void
code::CodeFunction::setBody(const std::string& aBody) noexcept
{
    mBody = aBody;
}

void
code::CodeFunction::outputToHpp(std::ofstream& aOut) const noexcept
{
    if (mIsVariadic)
    {
        aOut << "template <typename... Args>";
    }
    if (mIsStatic) aOut << "static ";
    aOut << mType << "\n";
    aOut << mName << "(" << mArguments;
    if (mIsVariadic)
    {
        aOut << ", "
             << "Args&&... args";
    }

    if (!mTemplate.empty() || mIsVariadic)
    {
        aOut << ")\n{\n" << mBody << "}\n\n";
    }
    else
    {
        aOut << ");\n";
    }
}

void
code::CodeFunction::outputToCpp(std::ofstream& aOut) const noexcept
{
    if (!(!mTemplate.empty() || mIsVariadic))
    {
        aOut << mType << "\n";
        aOut << mNamespace << "::" << mClass << "::" << mName << "("
             << mArguments << ")\n{\n"
             << mBody << "}\n";
    }
}

void
code::CodeFunction::makeRouter(std::string aMapName) noexcept
{
    mArguments = "const std::string& aName";

    std::string execExpr;
    if (mIsFunctor) execExpr = "()";
    if (mIsVariadic) execExpr = "(args...)";

    mBody = "decltype(" + aMapName + ".begin()->second(args...)" + execExpr +
            ") result;\n"
            "auto it = " +
            aMapName +
            ".find(aName);\n"
            "if (it != " +
            aMapName +
            ".end())\n"
            "result= it->second(args...)" +
            execExpr +
            ";"
            "return result;\n";
}
