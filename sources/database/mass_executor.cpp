#include "mass_executor.hpp"

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
