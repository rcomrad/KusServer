#include "table_info.hpp"

#include "kernel/framework/logger/basic/exception.hpp"

//------------------------------------------------------------------------------

void
core::TableInfo::newLine()
{
    addSubline();
    m_subline_indx = 0;
}

void
core::TableInfo::nextStep()
{
    switch (m_step)
    {
        case Step::CONSTRUCT:
            m_step         = Step::CALCULATE;
            m_subline_indx = 0;
            break;
        case Step::CALCULATE:
            m_step = Step::PRINT;
            prepareForPrinting();
            break;
        default:
            THROW("Trying to move to the next step in the table printer after "
                  "the last step has been reached.");
            break;
    }
    m_column_indx = 0;
}

void
core::TableInfo::addSubline()
{
    if (m_step == Step::CALCULATE)
    {
        m_row_count++;
    }
    else if (m_step == Step::PRINT)
    {
        for (; m_column_indx < m_columns.size(); ++m_column_indx)
        {
            m_columns.at(m_column_indx).pass(&m_buffer);
        }
        m_buffer += sprintf(m_buffer, "\n%c", m_separator);
    }
    m_column_indx = 0;
}

void
core::TableInfo::finish()
{
    *(m_buffer - 1) = 0;
    m_columns.clear();
    m_sublines.clear();
}

//------------------------------------------------------------------------------

void
core::TableInfo::clear()
{
    m_separator    = '|';
    m_step         = Step::CONSTRUCT;
    m_row_count    = 1;
    m_column_indx  = 0;
    m_subline_indx = 0;
    m_columns.clear();
    m_sublines.clear();
    m_result        = nullptr;
    m_printing_head = true;
}

void
core::TableInfo::prepareForPrinting()
{
    int size = 0;
    for (auto& i : m_sublines)
    {
        i.getWidth();
    }
    for (auto& i : m_columns)
    {
        size += i.getWidth();
    }
    size += 2;
    size *= m_row_count;

    m_result             = std::make_unique<char[]>(size + 1);
    m_result.get()[size] = 0;
    m_result.get()[0]    = m_separator;
    m_buffer             = m_result.get() + 1;

    if (m_printing_head)
    {
        for (; m_column_indx < m_columns.size(); ++m_column_indx)
        {
            m_columns[m_column_indx].printHead(&m_buffer);
        }
        newLine();
    }
}

std::unique_ptr<char[]>
core::TableInfo::getResult()
{
    auto result = std::move(m_result);
    clear();
    return result;
}

//------------------------------------------------------------------------------

void
core::TableInfo::setDefaultSeparator(char a_separator)
{
    m_separator = a_separator;
}

core::ColumnInfo&
core::TableInfo::getKeyInfo()
{
    return m_columns[0].turnOn();
}

void
core::TableInfo::noHead()
{
    m_printing_head = false;
}

//------------------------------------------------------------------------------
