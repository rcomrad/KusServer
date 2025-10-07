#include "mass_executor.hpp"

#include "kernel/framework/logger/include_me.hpp"

namespace database
{

void
MassExecutor::createAll(SQLConnection& a_conn)
{
    call(CallType::CREATE, a_conn);
}

void
MassExecutor::deleteAll(SQLConnection& a_conn)
{
    call(CallType::DELETE, a_conn);
}

std::string
MassExecutor::dumpAll(SQLConnection& a_conn)
{
    std::string result;
    std::any bus = &result;
    call(CallType::DUMP, a_conn, bus);
    return result;
}

void
MassExecutor::load(SQLConnection& a_conn,
                   const std::vector<std::string>& a_data)
{
    std::string cur_name;
    std::vector<std::string_view> temp;
    for (auto& i : a_data)
    {
        if (i.empty()) continue;
        if (i.at(0) == '#') continue;

        if (i.back() == '@')
        {
            cur_name = i;
            cur_name.pop_back();
            temp.clear();
            continue;
        }

        if (i.back() == '~')
        {
            auto it = m_exsiting_types.find(cur_name);
            if (it == m_exsiting_types.end())
            {
                LOG_ERROR("No table with name '%s'", cur_name);
                continue;
            }

            std::any bus = &temp;
            it->second(CallType::LOAD, a_conn, bus);
            continue;
        }

        temp.emplace_back(i);
    }
}

void
MassExecutor::call(CallType a_type, SQLConnection& a_conn)
{
    std::any dummy;
    call(a_type, a_conn, dummy);
}

void
MassExecutor::call(CallType a_type, SQLConnection& a_conn, std::any& a_data)
{
    for (auto& [_, lumbda] : m_exsiting_types)
    {
        lumbda(a_type, a_conn, a_data);
    }
}

} // namespace database
