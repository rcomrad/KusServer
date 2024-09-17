#include "table_printer.hpp"

#define CAST(to, whom) (*reinterpret_cast<to*>(const_cast<char*>(whom)))

#define PRINT_CASE(type_enum, type, expression)                                \
    case util::TypeID::type_enum:                                              \
        res = snprintf(a_buffer, mx_size, " %-*" type " |", width, expression); \
        break;

void
core::TablePrinter::print(const core::TableInfo& a_info,
                          const char* a_data_ptr,
                          char*& a_buffer,
                          std::vector<size_t>& a_sizes,
                          bool a_is_draft,
                          size_t& a_num) noexcept
{
    for (auto& info : a_info.m_columns)
    {
        if (a_sizes.size() == a_num)
        {
            a_sizes.emplace_back(0);
        }

        auto* ptr = a_data_ptr + info.offset;

        switch (info.cell_type)
        {
            case TableInfo::CellType::COLUMN:
                printColumn(info.var_t_id, ptr, a_buffer, a_sizes, a_is_draft,
                            a_num);
                break;
            case TableInfo::CellType::ROW:
                print(TableStorage::getTableInfo(
                          std::type_index(info.var_t_indx)),
                      a_data_ptr, a_buffer, a_sizes, a_is_draft, a_num);
                break;
        }
    }
}

void
core::TablePrinter::printColumn(util::TypeID a_type,
                                const char* a_ptr,
                                char*& a_buffer,
                                std::vector<size_t>& a_sizes,
                                bool a_is_draft,
                                size_t& a_num) noexcept
{
    size_t res     = 0;
    size_t mx_size = a_is_draft ? 0 : (a_sizes[a_num] + 1);
    int width      = a_is_draft ? 0 : (a_sizes[a_num] - 3);
    if (width < 0)
        width = 0; // TODO: code  works without it somehow, investigate
    switch (a_type)
    {
        PRINT_CASE(S_INT_32, "d", CAST(int32_t, a_ptr))
        PRINT_CASE(U_INT_32, "u", CAST(uint32_t, a_ptr))
        PRINT_CASE(FLOAT, ".3f", CAST(float, a_ptr))
        PRINT_CASE(DOUBLE, ".3lf", CAST(double, a_ptr))
        PRINT_CASE(BOOL, "s", CAST(bool, a_ptr) ? "true" : "false")
        PRINT_CASE(CHAR_PTR, "s", a_ptr)
        PRINT_CASE(STRING, "s", CAST(std::string, a_ptr).c_str())
        PRINT_CASE(STRING_VIEW, "s", CAST(std::string_view, a_ptr).data())
    }

    if (!a_is_draft)
    {
        a_buffer += res;
    }
    else
    {
        a_sizes[a_num] = std::max(a_sizes[a_num], res);
    }
    ++a_num;
}
