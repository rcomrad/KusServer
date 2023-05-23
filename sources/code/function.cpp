#include "function.hpp"

code::Function::Function() noexcept
{
    mIsStatic   = false;
    mIsFunctor  = false;
    mIsVariadic = false;
    mType       = "auto";
}

void
code::Function::setNamespace(const std::string& aNamespace) noexcept
{
    mNamespace = aNamespace;
}

void
code::Function::setClass(const std::string& aClass) noexcept
{
    mClass = aClass;
}

void
code::Function::makeStatic() noexcept
{
    mIsStatic = true;
}

void
code::Function::makeFunctor() noexcept
{
    mIsFunctor  = true;
    mIsVariadic = false;
}

void
code::Function::makeVariadic() noexcept
{
    mIsFunctor  = false;
    mIsVariadic = true;
}

void
code::Function::setTemplate(const std::string& aTemplate) noexcept
{
    mTemplate = aTemplate;
}

void
code::Function::setReturnType(const std::string& aType) noexcept
{
    mType = aType;
}

void
code::Function::setName(const std::string& aName) noexcept
{
    mName = aName;
}

void
code::Function::setArguments(const std::string& aArguments) noexcept
{
    mArguments = aArguments;
}

void
code::Function::setBody(const std::string& aBody) noexcept
{
    mBody = aBody;
}

void
code::Function::outputToHpp(std::ofstream& aOut) const noexcept
{
    aOut << mType << "\n";
    if (mIsStatic) aOut << "static ";
    aOut << mName << "(" << mArguments;
    if (mIsVariadic)
    {
        aOut << ", "
             << "Args&& args";
    }

    if (!mTemplate.empty() || mIsVariadic)
    {
        aOut << ")\n{\n" << mBody << "}\n";
    }
    else
    {
        aOut << ");\n";
    }
}

void
code::Function::outputToCpp(std::ofstream& aOut) const noexcept
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
code::Function::makeRouter(std::string aMapName) noexcept
{
    mArguments = "const std::string& aName";

    std::string execExpr;
    if (mIsFunctor) execExpr = "()";
    if (mIsVariadic) execExpr = "(args...)";

    mBody = "decltype(" + aMapName + ".begin()->second" + execExpr +
            ") result;\n"
            "auto it = " +
            aMapName +
            ".find(aName);\n"
            "if (it != " +
            aMapName +
            ".end())\n"
            "result= it->second" +
            execExpr +
            ";"
            "return result;\n";
}
