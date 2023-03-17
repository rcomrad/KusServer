// #include "get_request.hpp"

// #include <iostream>

// #include "asterisk_hendler.hpp"

// #define string_view string

// std::unordered_map<std::string_view, std::string_view>
//     serv::GetRequest::allTranslateTable = {
//         {"methodist", "user"},
//         {"teacher",   "user"},
//         {"head",      "user"},
//         {"student",   "user"}
// };

// serv::GetRequest::GetRequest()
// {
// }

// #include <span>

// // TODO: For stupid GNU! (it cant use constructor from iterators)
// auto
// makeStrView(std::string_view& aStr,
//             std::string_view ::const_iterator aFrom,
//             std::string_view ::const_iterator aTo)
// {
//     // std::string_view result(aStr.data() + (aFrom - aStr.begin()), aTo -
//     // aFrom);
//     // std::span<const char> result(aFrom, aTo);
//     // std::string_view result(aFrom, aTo);
//     std::string result(aFrom, aTo);
//     return result;
// }

// serv::GetRequest::GetRequest(std::string_view aStr, std::string_view aTableName)
// {
//     auto it         = aStr.begin();
//     bool flag       = true;
//     bool insertFlag = true;
//     auto old        = it;
//     if (aTableName.empty())
//     {
//         while (++it != aStr.end() && (flag = *it != '[') &&
//                (insertFlag = *it != '('))
//             old = it;
//         name = makeStrView(aStr, aStr.begin(), it);
//     }
//     else
//     {
//         flag = false;
//         name = aTableName;
//     }
//     old = it;

//     if (!insertFlag)
//     {
//         while (it != aStr.end())
//         {
//             if (*it == ';' || *it == ')' || *it == '[')
//             {
//                 // inserts.emplase_back(std::string_view(old, it));
//                 std::string_view temp = makeStrView(aStr, old + 1, it);
//                 old                   = it;
//                 if (*it == '[')
//                 {
//                     int brackets = 1;
//                     while (!(*(++it) == ']' && brackets == 1))
//                     {
//                         if (*it == ']') brackets--;
//                         if (*it == '[') brackets++;
//                     }
//                 }
//                 args[temp] = makeStrView(aStr, old, it + 1);
//                 old        = it;
//                 if (*it == ')') break;
//                 if (*(it + 1) == ')')
//                 {
//                     ++it;
//                     break;
//                 }
//             }

//             // for (auto& i : inserts) std::cout << i << " ";
//             // std::cout << "\n";

//             ++it;
//         }
//         ++it;
//         if (it != aStr.end())
//         {
//             flag = *it != '[';
//             old  = it;
//         }
//     }

//     int brackets = 1;
//     std::string_view prev;
//     while (!flag)
//     {
//         if (++it == aStr.end()) break;

//         if (*it == ']') brackets--;
//         if (*it == '[') brackets++;

//         if (brackets == 2 && *it == '[' || brackets == 1 && *it == ';' ||
//             brackets == 0)
//         {
//             if (old + 1 != it)
//             {
//                 // elements.push_back(std::string_view(old + 1, it));
//                 // args.push_back(std::string_view(s.begin(), s.begin()));
//                 prev = makeStrView(aStr, old + 1, it);
//                 args[prev];
//             }
//             old = it;
//         }
//         if (brackets == 1 && *it == ']')
//         {
//             // args.back() = std::string_view(old + 1, it);
//             args[prev] = makeStrView(aStr, old, it + 1);
//             old        = it;
//         }
//         if (brackets == 0) flag ^= true;
//     }

//     if (!flag)
//     {
//         // elements.clear();
//         args.clear();
//         inserts.clear();
//     }
//     else
//     {
//     }

//     auto transIT = allTranslateTable.find(name);
//     if (transIT != allTranslateTable.end())
//     {
//         name =
//             makeStrView(aStr, transIT->second.begin(), transIT->second.end());
//     }

//     if (aStr == "[]") args["*"];

//     reset(aTableName);
// }

// void
// serv::GetRequest::reset(std::string_view aTableName)
// {
//     auto itt = args.find("*");
//     if (allTranslateTable.find(aTableName) != allTranslateTable.end())
//     {
//         aTableName = allTranslateTable.find(aTableName)->second;
//     }
//     if (itt != args.end())
//     {
//         for (auto& i : AsteriskHendler::table[aTableName])
//         {
//             args[i];
//         }
//     }
// }

// boost::optional<std::pair<std::string_view, std::string_view>>
// serv::GetRequest::operator[](std::string_view aStr)
// {
//     boost::optional<std::pair<std::string_view, std::string_view>> res{};

//     auto it = args.find(aStr);
//     // if (it == args.end())
//     // {
//     //     it = args.find("*");
//     // }
//     if (it != args.end())
//     {
//         res = *it;
//     }

//     return res;
// }
