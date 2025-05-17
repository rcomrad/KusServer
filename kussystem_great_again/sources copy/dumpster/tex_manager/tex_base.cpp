#include "tex_base.hpp"

#include "file_data/parser.hpp"

tex::TexBase::TexBase(std::unordered_map<str::String, std::vector<str::String>>*
                          aVariables) noexcept
    : mVariables(aVariables)
{
}

str::String
tex::TexBase::getVariable(const char* aName) noexcept
{
    str::String result;

    if (mVariables != nullptr && aName.find('$') != str::String::npos)
    {
        str::String name = file::Parser::slice(aName, " ")[0];
        auto it          = mVariables->find(name);
        if (it != mVariables->end() && it->second.size() > 0)
        {
            result = it->second.back();
            it->second.pop_back();
        }
    }

    if (result.empty())
    {
        result = aName;
    }

    return result;
}
