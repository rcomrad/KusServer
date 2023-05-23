#include "class.hpp"

std::unordered_map<std::string, std::string> code::Class::globalPaths = {
    {"post", "../sources/post/"},
    {"get",  "../sources/get/" }
};

void
code::Class::setName(const std::string& aName) noexcept
{
    mName     = aName;
    mFileName = mName;

    mName[0] = std::toupper(mName[0]);
    int it   = mName.find('_');
    while (it != std::string::npos)
    {
        mName[it + 1] = std::toupper(mName[it + 1]);
        mName.erase(it);
        it = mName.find('_');
    }

    mFileName[0] = std::tolower(mFileName[0]);
    for (int i = 0; i < mFileName.size(); ++i)
    {
        if (mFileName[i] >= 'A' && mFileName[i] <= 'Z')
        {
            mFileName[i] = std::tolower(mFileName[i]);
            mFileName.insert(mFileName.begin() + i, '_');
        }
    }

    reloadName();
}

void
code::Class::setNamespace(const std::string& aNamespace) noexcept
{
    mNamespace = aNamespace;
    reloadName();
}

void
code::Class::addRouterFunction(const std::string& aName,
                               const std::string& aType,
                               const std::string& aBody) noexcept
{
    std::string variableName = "m" + aName;
    variableName[1]          = std::toupper(variableName[1]);

    mFunctions.emplace_back();
    auto& funk = mFunctions.back();
    funk.makeStatic();
    funk.setName(aName);
    funk.setClass(mName);
    funk.setNamespace(mNamespace);
    funk.makeRouter(variableName);
    funk.setArguments("std::string aName");

    mStaticVariables.emplace_back();
    auto& var = mStaticVariables.back();
    var.setClass(mName);
    var.setNamespace(mNamespace);
    var.setName(variableName);
    var.setType("std::unordered_map<std::string, " + aType);
    var.setInitialisation(aBody);
}

void
code::Class::addFuncRouterForDatabase(const std::string& aName,
                                      const std::string& aFunction,
                                      const std::string& aBody) noexcept
{
    addRouterFunction(aName, "decltype(&" + aFunction + "<data::Dummy>)",
                      aBody);
    auto& funk = mFunctions.back();
    funk.makeVariadic();
}

void
code::Class::reloadName() noexcept
{
    mFilePath = globalPaths[mNamespace] + mFileName;
}
