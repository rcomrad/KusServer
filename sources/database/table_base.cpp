#include "table_base.hpp"

namespace database
{

TableBase::TableBase(int a_id) : id(a_id)
{
}

void
TableBase::selectBase(database::PostgreSQL& a_psql)
{
    id = a_psql.getInt(0);
}

void
TableBase::insertBase(util::StringBuilder& a_sb) const
{
    if (id == 0) a_sb.add("default");
    else a_sb.add(id);
    a_sb.add(',');
}

void
TableBase::addInfo(std::string& a_info, std::string_view a_name, int)
{
    a_info += a_name;
    a_info += " INTEGER NOT NULL,";
}

void
TableBase::addInfo(std::string& a_info,
                   std::string_view a_name,
                   const std::string&)
{
    a_info += a_name;
    a_info += " VARCHAR(50) NOT NULL,";
}

std::string
TableBase::dumpType(int a_data)
{
    return addSeparator(std::to_string(a_data));
}

std::string
TableBase::dumpType(std::string a_data)
{
    return addSeparator(std::string(a_data));
}

void
TableBase::loadType(std::string_view a_data, int& a_res)
{
    a_res = std::stoi(std::string(a_data));
}

void
TableBase::loadType(std::string_view a_data, std::string& a_res)
{
    a_res = a_data;
}

std::string
TableBase::addSeparator(std::string&& a_data)
{
    std::string result = std::move(a_data);
    result.push_back(';');
    return result;
}

} // namespace database
