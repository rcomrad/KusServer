#pragma once

#include <cstring>
#include <string>
#include <typeindex>
#include <vector>

#include "utility/string/print_type.hpp"
#include "utility/type/base.hpp"
#include "utility/type/kus_type_info.hpp"

namespace core
{

struct TableInfo
{
    enum class CellType
    {
        NUN,
        COLUMN,
        ROW,
        END
    };

    TableInfo() noexcept = default;

    template <typename T>
    TableInfo(const T& obj) noexcept
    {
        base_ptr = reinterpret_cast<addr_t>(&obj);
    }

    template <typename... Args>
    TableInfo& addCol(const Args&... args) noexcept
    {
        (m_columns.emplace_back(
             CellType::COLUMN, reinterpret_cast<addr_t>(&args) - base_ptr,
             util::TypeInfo::getTypeId<Args>(), std::type_index(typeid(void))),
         ...);

        return *this;
    }

    template <typename... Args>
    TableInfo& addRow(const Args&... args) noexcept
    {
        (m_columns.emplace_back(
             CellType::ROW, reinterpret_cast<addr_t>(&args) - base_ptr,
             util::TypeID ::NUN, std::type_index(typeid(Args))),
         ...);
        return *this;
    }

    struct ColumnData
    {
        CellType cell_type;
        addr_t offset;
        util::TypeID var_t_id;
        std::type_index var_t_indx;
    };
    addr_t key_size;
    std::vector<ColumnData> m_columns;

private:
    addr_t base_ptr;
};

} // namespace core
