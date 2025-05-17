#pragma once

#include "table_info.hpp"

namespace core
{

class LocalTableInfo
{
public:
    static TableInfo& getTableInfo() noexcept;
};

} // namespace core

#define TABLE_INFO core::LocalTableInfo::getTableInfo()
