#include "table_storage.hpp"

#include "core/logging/logging.hpp"

SINGLETON_DEFINITOR(core, TableStorage)

void
core::TableStorage::addTableInfoNonstatic(std::type_index a_type,
                                          const TableInfo& a_info) noexcept
{
    if (m_data_storage.find(a_type) != m_data_storage.end())
    {
        LOG_ERROR("Table info for '%s' type already exist.", a_type.name());
        return;
    }
    m_data_storage[a_type] = a_info;
}

const core::TableInfo&
core::TableStorage::getTableInfoNonstatic(std::type_index a_type) noexcept
{
    auto it = m_data_storage.find(a_type);
    if (it == m_data_storage.end())
    {
        LOG_ERROR("Table info for '%s' type doesn't exist.", a_type.name());
        return m_dumy;
    }
    return it->second;
}
