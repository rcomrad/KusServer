#include "value.hpp"

#include <unordered_set>

#include "parser.hpp"

file::Value::operator int() const noexcept
{
    return std::stoi(str);
}

file::Value::operator float() const noexcept
{
    return std::stof(str);
}

file::Value::operator bool() const noexcept
{
    bool result     = false;
    auto normalised = Parser::normalize(str, Parser::Type::Lower);
    if (normalised == "on" || normalised == "yes") result = true;
    return result;
}

file::Value::operator std::string() const noexcept
{
    return str;
}

file::Value::operator dom::Pair<float>() const noexcept
{
    dom::Pair<float> result;

    int cur = 0;
    std::string temp;
    bool flag = true;
    for (int cur = 0; cur < str.size() + 1; ++cur)
    {
        if (std::isdigit(str[cur]) || str[cur] == '.')
        {
            temp += str[cur];
        }
        else
        {
            if (temp.size())
            {
                if (flag)
                {
                    result.x = std::stof(temp);
                }
                else
                {
                    result.y = std::stof(temp);
                }
                temp.clear();
                flag = !flag;
            }
        }
    }

    return result;
}

file::Value::Type
file::Value::getType() const noexcept
{
    Value::Type result = Value::Type::Nun;

    auto normalised = Parser::normalize(str, Parser::Type::Lower);
    std::unordered_set<char> characters;
    for (auto i : normalised)
    {
        if (std::islower(i)) i = 'a';
        else if (std::isdigit(i)) i = '0';
        else if (i != '.' && i != '-' && i != ',') i = '?';

        characters.insert(i);
    }
    if (normalised == "yes" || normalised == "no")
    {
        result = Value::Type::Bool;
    }
    else if (characters.count('a') == 0 && characters.count('?') == 0)
    {
        if (characters.count(','))
        {
            if (characters.count('.'))
            {
                result = Value::Type::PairFloat;
            }
            else
            {
                result = Value::Type::PairInt;
            }
        }
        else if (characters.count('.'))
        {
            result = Value::Type::Float;
        }
        else
        {
            result = Value::Type::Int;
        }
    }
    else
    {
        result = Value::Type::String;
    }

    return result;
}
