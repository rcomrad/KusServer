#pragma once

#include <typeindex>
#include <unordered_map>

#include "utility/common/holy_trinity.hpp"

#include "table_info.hpp"

namespace core
{

class TableStorage
{
public:
    HOLY_TRINITY_SINGLETON(TableStorage);
    SINGL_VOID_METHOD(addTableInfo,
                      (std::type_index a_type, const TableInfo& a_info));
    SINGL_RET_METHOD(const TableInfo&, getTableInfo, (std::type_index a_type));

private:
    TableInfo m_dumy;
    std::unordered_map<std::type_index, TableInfo> m_data_storage;

    TableStorage() noexcept = default;
};

#define TABLE_REGISTER_HPP(class_name, ...)                                \
    struct class_name##TABLE_REGISTER                                      \
    {                                                                      \
        inline class_name##TABLE_REGISTER() noexcept                       \
        {                                                                  \
            class_name* obj_ptr = nullptr;                                 \
            class_name& obj     = *obj_ptr;                                \
            core::TableInfo info(obj);                                     \
            info __VA_ARGS__;                                              \
            core::TableStorage::addTableInfo(std::type_index(typeid(obj)), \
                                             info);                        \
        }                                                                  \
    };                                                                     \
    static class_name##TABLE_REGISTER class_name##TABLE_REGISTER##global;

#define TABLE_REGISTER_CPP(space, class_name)     \
    space::class_name::class_name##TABLE_REGISTER \
        space::class_name::class_name##TABLE_REGISTER##global;

} // namespace core
