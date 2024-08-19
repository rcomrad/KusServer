#pragma once

#include <string>
#include <vector>

#include "utility/common/metaprogramming.hpp"
#include "utility/type/base.hpp"

#include "column_view.hpp"

namespace core
{

// TODO: make private
constexpr auto FORMAT_MAX_SZ = 25;

class TablePrintHelper
{
public:
    TablePrintHelper() noexcept;

    void pushColumn(const ColumnView& a_column_view) noexcept;

    void printHead(char** a_ptr) noexcept;
    void printLine(char** a_ptr) noexcept;
    template <typename T>
    void printData(char** a_ptr, T a_data) noexcept
    {
        *a_ptr += sprintf(*a_ptr, m_format[m_fromat_it++].c_str(), a_data);
        if (m_fromat_it >= m_format.size())
        {
            *a_ptr += sprintf(*a_ptr, "|\n");
            m_fromat_it = 0;
            printLine(a_ptr);
        }
    }

    size_t getSize() noexcept;

private:
    int m_fromat_it;
    size_t m_combined_size;
    std::string m_head;
    std::vector<std::string> m_format;
};

#define PUSH_BASIC_COLUMN(...) a_table.pushColumn(BASIC_COLUMN(__VA_ARGS__))
#define PUSH_SIZED_COLUMN(...) a_table.pushColumn(SIZED_COLUMN(__VA_ARGS__))
#define PUSH_NAMED_COLUMN(...) a_table.pushColumn(NAMED_COLUMN(__VA_ARGS__))
#define PUSH_COMBINED_COLUMN(...) \
    a_table.pushColumn(COMBINED_COLUMN(__VA_ARGS__))

} // namespace core
