#pragma once

#include <string>
#include <string_view>

#include "kernel/utility/string/string_builder.hpp"

#include "postgresql.hpp"

namespace database
{

template <typename DatabaseTableT>
class TableSpecific
{
public:
    std::string_view getTableName()
    {
        // exception
        // assert
        return "error";
    }

    void insert(char*& a_ptr)
    {
    }

    void select(char*& a_ptr)
    {
    }
};

struct User
{
    int id;
    std::string login;
    std::string password;
    std::string last_login;
};

template <>
class TableSpecific<User>
{
public:
    std::string_view getTableName()
    {
        return "user";
    }

    void insert(util::StringBuilder& a_sb, const User& a_data)
    {
        auto scoped = a_sb.addSeparator(',');
        // a_sb.add(a_data.id);
        a_sb.add(a_data.login);
        a_sb.add(a_data.password);
        a_sb.add(a_data.last_login);
    }

    void select(PostgreSQL& a_psql, User& a_data)
    {
        a_data.id         = a_psql.getInt(0);
        a_data.login      = std::string(a_psql.getChars(1));
        a_data.password   = std::string(a_psql.getChars(2));
        a_data.last_login = std::string(a_psql.getChars(3));
    }
};

} // namespace data
