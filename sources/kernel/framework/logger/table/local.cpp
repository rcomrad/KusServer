#include "local.hpp"

core::TableInfo&
core::LocalTableInfo::getTableInfo() noexcept
{
    thread_local TableInfo instance;
    return instance;
}
