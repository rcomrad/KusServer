// #ifndef GET_REQUEST_HPP
// #define GET_REQUEST_HPP

// #include <optional>
// #include <string>
// #include <string_view>
// #include <unordered_map>
// #include <vector>

// #include "boost/optional.hpp"

// #define string_view string

// namespace serv
// {

// struct GetRequest
// {
//     GetRequest();

//     GetRequest(std::string_view aStr, std::string_view aTableName = "");

//     // void print()
//     // {
//     //     std::cout << "name: " << name << " " << elements.size() << " "
//     //               << args.size() << "\n";
//     //     for (int i = 0; i < elements.size(); ++i)
//     //         std::cout << "\t" << elements[i] << ": " << args[i] << "\n";
//     // }

//     std::string_view name;
//     // std::vector<std::string_view> elements;
//     // std::vector<std::string_view> args;
//     std::unordered_map<std::string_view, std::string_view> args;

//     boost::optional<std::pair<std::string_view, std::string_view>> operator[](
//         std::string_view aStr);
//     // {
//     //     boost::optional<std::pair<std::string_view, std::string_view>&>
//     //     res{}; auto it = args.find(aStr); if (it != args.end())
//     //     {
//     //         res = *it;
//     //     }
//     //     return res;
//     // }

//     auto begin()
//     {
//         return args.begin();
//     }

//     auto end()
//     {
//         return args.end();
//     }

//     void reset(std::string_view aTableName);

// private:
//     static std::unordered_map<std::string_view, std::string_view>
//         allTranslateTable;
//     std::vector<std::string_view> inserts;
// };

// } // namespace serv

// #undef string_view

// #endif // !GET_REQUEST_HPP
