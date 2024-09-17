#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "utility/type/base.hpp"

#include "struct_data.hpp"

namespace data
{

class StructStorage
{
public:
    static struct_id_t registrateStruct(const char* a_struct_name,
                                        const char* a_struct_vars) noexcept;
    static StructData& getStructData(struct_id_t a_struct_id) noexcept;
    static void shrinkToFit() noexcept;
    static size_t getSize() noexcept;

private:
    std::vector<StructData> m_struct_data;

    StructStorage() noexcept = default;
    static StructStorage& getInstance() noexcept;

    struct_id_t registrateStructNonstatic(const char* a_struct_name,
                                          const char* a_struct_vars) noexcept;
};

} // namespace data
