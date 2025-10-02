#pragma once

#include <any>
#include <functional>
#include <string>
#include <unordered_map>

#include "kernel/utility/macroses/holy_trinity.hpp"

#include "sql_connection.hpp"

namespace database
{

class MassExecutor
{
    enum class CallType
    {
        NUN,
        CREATE,
        DELETE,
        DUMP
    };

    using FuncType =
        std::function<void(CallType a_type, SQLConnection& a_conn, std::any&)>;

public:
    template <typename TableType>
    class Registrator
    {
    public:
        Registrator()
        {
            MassExecutor::getInstance().add<TableType>();
        }
    };

    HOLY_TRINITY_SINGLETON(MassExecutor);

    template <typename TableType>
    void add()
    {
        auto lambda =
            [](CallType a_type, SQLConnection& a_conn, std::any& a_data)
        {
            std::string* str_ptr = nullptr;
            switch (a_type)
            {
                case CallType::CREATE:
                    a_conn.createTable<TableType>();
                    break;
                case CallType::DELETE:
                    a_conn.deleteTable<TableType>();
                    break;
                case CallType::DUMP:
                    str_ptr = std::any_cast<std::string*>(a_data);
                    *str_ptr += a_conn.dump<TableType>();
                    break;
            }
        };

        m_exsiting_types[std::string(TableType::getTableName())] =
            std::move(lambda);
    }

    void createAll(SQLConnection& a_conn);
    void deleteAll(SQLConnection& a_conn);
    std::string dumpAll(SQLConnection& a_conn);

private:
    std::unordered_map<std::string, FuncType> m_exsiting_types;

    MassExecutor() = default;
    void call(CallType a_type, SQLConnection& a_conn);
    void call(CallType a_type, SQLConnection& a_conn, std::any& a_data);
};

} // namespace database
