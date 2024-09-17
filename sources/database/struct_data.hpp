#pragma once

#include "utility/type/base.hpp"

namespace data
{

enum
{
    DatabaseStructNameMaxSize = 31,
    DatabaseStructVarMaxCount = 20,
    DatabaseColumnNameMaxSize = 15,
};

using struct_id_t = word_t;

// template <uint8_t NameSize, uint8_t Count>
struct StructData
{
private:
    struct TypeData
    {
        util::TypeID type;
        size_t size;
        char name[DatabaseColumnNameMaxSize];
    };

public:
    char name[DatabaseStructNameMaxSize];
    uint8_t count;
    uint32_t str_max_size;
    uint16_t column_names_size = 0;
    TypeData vars[DatabaseStructVarMaxCount];
};

}; // namespace data
