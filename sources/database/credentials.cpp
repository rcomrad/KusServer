#include "credentials.hpp"

namespace database
{

Credentials::Credentials(const std::vector<std::string>& arguments)
{
    if (arguments.size() != COUNT) throw;

    user = std::move(arguments[0]);
    password = std::move(arguments[1]);
    hostaddr = std::move(arguments[2]);
    port = std::move(arguments[3]);
    db_name = std::move(arguments[4]);
}

} // namespace database
