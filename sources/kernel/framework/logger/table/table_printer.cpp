#include "table_printer.hpp"

#include "local.hpp"

std::unique_ptr<char[]>
core::TablePrinter::buildTable() const
{
    TABLE_INFO.clear();
    print();
    return TABLE_INFO.getResult();
}

void
core::TablePrinter::setDefaultSeparator(char a_separator) const
{
    TABLE_INFO.setDefaultSeparator(a_separator);
}

core::ColumnInfo&
core::TablePrinter::getKeyInfo() const
{
    return TABLE_INFO.getKeyInfo();
}
