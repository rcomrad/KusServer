#pragma once

#include <string>
#include <string_view>

#include "kernel/utility/string/string_builder.hpp"

#include "postgresql.hpp"

namespace database
{

// TODO: move table name here
struct TableBase
{
public:
    int id;

protected:
    TableBase(int a_id = 0);

    void selectBase(database::PostgreSQL& a_psql);
    void insertBase(util::StringBuilder& a_sb) const;

    static void addInfo(std::string& a_info, std::string_view a_name, int);
    static void addInfo(std::string& a_info,
                        std::string_view a_name,
                        const std::string&);

    static std::string dumpType(int a_data);
    static std::string dumpType(std::string a_data);

    static void loadType(std::string_view a_data, int& a_res);
    static void loadType(std::string_view a_data, std::string& a_res);

private:
    static std::string addSeparator(std::string&& a_data);
};

} // namespace database
