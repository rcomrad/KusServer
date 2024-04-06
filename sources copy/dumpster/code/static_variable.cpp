#include "static_variable.hpp"

void
code::StaticVariable::setNamespace(const std::string& aNamespace) noexcept
{
    mNamespace = aNamespace;
}

void
code::StaticVariable::setClass(const std::string& aClass) noexcept
{
    mClass = aClass;
}

void
code::StaticVariable::setType(const std::string& aType) noexcept
{
    mType = aType;
}

void
code::StaticVariable::setName(const std::string& aName) noexcept
{
    mName = aName;
}

void
code::StaticVariable::setInitialisation(
    const std::string& aInitialisation) noexcept
{
    mInitialisation = aInitialisation;
}

void
code::StaticVariable::outputToHpp(std::ofstream& aOut) const noexcept
{
    aOut << "static " << mType << " " << mName << ";\n";
}

void
code::StaticVariable::outputToCpp(std::ofstream& aOut) const noexcept
{
    aOut << mType << " " << mNamespace << "::" << mClass << "::" << mName
         << " = {" << mInitialisation << "};\n";

    if (mInitialisation.size() > 1000) aOut << "\n";
}
