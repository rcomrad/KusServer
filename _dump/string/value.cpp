// #include "value.hpp"

// #include <unordered_set>

// #include "parser.hpp"

// str::Value::operator int() const noexcept
// {
//     return std::stoi(str);
// }

// str::Value::operator float() const noexcept
// {
//     return std::stof(str);
// }

// str::Value::operator bool() const noexcept
// {
//     bool result     = false;
//     auto normalised = Parser::normalize(str, Parser::Type::LOWER);
//     if (normalised == "on" || normalised == "yes" || normalised == "true")
//         result = true;
//     return result;
// }

// str::Value::operator std::string() const noexcept
// {
//     return str;
// }

// str::Value::operator core::Pair<float>() const noexcept
// {
//     core::Pair<float> result;

//     int cur = 0;
//     std::string temp;
//     bool flag = true;
//     for (int cur = 0; cur < str.size() + 1; ++cur)
//     {
//         if (std::isdigit(str[cur]) || str[cur] == '.')
//         {
//             temp += str[cur];
//         }
//         else
//         {
//             if (temp.size())
//             {
//                 if (flag)
//                 {
//                     result.x = std::stof(temp);
//                 }
//                 else
//                 {
//                     result.y = std::stof(temp);
//                 }
//                 temp.clear();
//                 flag = !flag;
//             }
//         }
//     }

//     return result;
// }

// str::Value::Type
// str::Value::getType() const noexcept
// {
//     Value::Type result = Value::Type::Nun;

//     auto normalised = Parser::normalize(str, Parser::Type::LOWER);
//     std::unordered_set<char> characters;
//     for (auto i : normalised)
//     {
//         if (std::islower(i)) i = 'a';
//         else if (std::isdigit(i)) i = '0';
//         else if (i != '.' && i != '-' && i != ',') i = '?';

//         characters.insert(i);
//     }
//     if (normalised == "yes" || normalised == "no" || normalised == "on" ||
//         normalised == "off" || normalised == "true" || normalised == "false")
//     {
//         result = Value::Type::Bool;
//     }
//     else if (characters.count('a') == 0 && characters.count('?') == 0)
//     {
//         if (characters.count(','))
//         {
//             if (characters.count('.'))
//             {
//                 result = Value::Type::PairFloat;
//             }
//             else
//             {
//                 result = Value::Type::PairInt;
//             }
//         }
//         else if (characters.count('.'))
//         {
//             result = Value::Type::Float;
//         }
//         else
//         {
//             result = Value::Type::Int;
//         }
//     }
//     else
//     {
//         result = Value::Type::String;
//     }

//     return result;
// }
