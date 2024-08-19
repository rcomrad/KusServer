#include "table_print_helper.hpp"

#include <cstring>
#include <memory>
#include <string>

core::TablePrintHelper::TablePrintHelper() noexcept
    : m_fromat_it(0), m_combined_size(1)
{
    m_head = "|\n";
}

void
core::TablePrintHelper::pushColumn(const ColumnView& a_column_view) noexcept
{
    const auto& size = a_column_view.size;
    m_combined_size += size + 1;
    
    std::string format_pref =
        "|%-" + std::to_string(size) + "." + std::to_string(size);
    std::unique_ptr<char[]> temp_head = std::make_unique<char[]>(size + 10);
    sprintf(temp_head.get(), (format_pref + "s").c_str(),
            a_column_view.name.c_str());
    m_head.resize(m_head.size() - 2);
    m_head += std::string(temp_head.get()) + "|\n";

    m_format.emplace_back("|%-" + std::to_string(size) + a_column_view.format);
}

void
core::TablePrintHelper::printHead(char** a_ptr) noexcept
{
    printLine(a_ptr);
    *a_ptr += sprintf(*a_ptr, "%s", m_head.c_str());
    printLine(a_ptr);
}

void
core::TablePrintHelper::printLine(char** a_ptr) noexcept
{
    *a_ptr += sprintf(
        *a_ptr, "%.*s\n", int(m_combined_size),
        "-------------------------------------------------------------------"
        "-------------------------------------------------------------------");
}

size_t
core::TablePrintHelper::getSize() noexcept
{
    return m_combined_size;
}
