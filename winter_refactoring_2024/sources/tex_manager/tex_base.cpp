#include "tex_base.hpp"

#include "text_data/parser.hpp"

tex::TexBase::TexBase(std::unordered_map<std::string, std::vector<std::string>>*
                          aVariables) noexcept
    : mVariables(aVariables)
{
}

std::string
tex::TexBase::getVariable(const std::string& aName) noexcept
{
    std::string result;

    if (mVariables != nullptr && aName.find('$') != std::string::npos)
    {
        std::string name = text::Parser::slice(aName, " ")[0];
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
