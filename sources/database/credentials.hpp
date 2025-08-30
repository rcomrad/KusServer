#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace database
{

struct Credentials
{
    static const size_t COUNT = 5;

    std::string user;
    std::string password;
    std::string hostaddr;
    std::string port;
    std::string db_name;

    Credentials(const std::vector<std::string>& arguments);
};

} // namespace database
