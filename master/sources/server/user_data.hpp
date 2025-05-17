#ifndef USER_DATA_HPP
#define USER_DATA_HPP

#include <boost/date_time/posix_time/posix_time.hpp>

#include <string>

#include "domain/holy_trinity.hpp"

namespace serv
{
struct UserData
{
    boost::posix_time::ptime time;
    std::string ip;
    std::string password;
    int falseLogin;
    int id;
    int role;
    bool inUse = false;
};

} // namespace serv

#endif // !USER_DATA_HPP
