#pragma once

#include <memory>
#include <vector>

#include "column_info.hpp"

namespace core
{

class TableInfo
{
public:
    void newLine();
    void nextStep();
    void addSubline();
    void finish();
    void noHead();

    void clear();
    std::unique_ptr<char[]> getResult();

    template <typename Data>
    void addKey(const Data& a_data)
    {
        getKeyInfo(false).resetType(a_data);
    }

    ColumnInfo& getKeyInfo(bool a_turn_on_flag = true);

    template <typename Data>
    ColumnInfo& addCell(const Data& a_data)
    {
        switch (m_step)
        {
            case Step::CONSTRUCT:
                m_columns.emplace_back(m_columns.size(), a_data);
                m_columns.back().setSeparator(m_separator);
                break;
            case Step::CALCULATE:
                m_columns.at(m_column_indx).takeIntoAccount(a_data);
                break;
            case Step::PRINT:
                m_columns.at(m_column_indx).print(&m_buffer, a_data);
                break;
        }

        return m_columns.at(m_column_indx++);
    }

    template <typename Data>
    ColumnInfo& addCell(int a_parant, const Data& a_data)
    {
        ColumnInfo& parant = m_columns.at(a_parant);
        switch (m_step)
        {
            case Step::CONSTRUCT:
                m_sublines.emplace_back(m_columns.size(), parant, a_data);
                m_sublines.back().setSeparator(m_separator);
                break;
            case Step::CALCULATE:
                m_sublines.at(m_subline_indx).takeIntoAccount(a_data);
                break;
            case Step::PRINT:
                for (; m_column_indx < (&parant - &m_columns.front());
                     ++m_column_indx)
                {
                    m_columns.at(m_column_indx).pass(&m_buffer);
                }
                m_sublines.at(m_subline_indx).print(&m_buffer, a_data);
                ++m_column_indx;
                break;
        }

        return m_sublines.at(m_subline_indx++);
    }

    void setDefaultSeparator(char a_separator);

private:
    enum Step
    {
        CONSTRUCT,
        CALCULATE,
        PRINT
    };

    Step m_step;
    int m_column_indx;
    int m_subline_indx;
    int m_row_count;
    std::vector<ColumnInfo> m_columns;
    std::vector<ColumnInfo> m_sublines;

    char m_separator;
    bool m_printing_head;

    char* m_buffer;
    std::unique_ptr<char[]> m_result;

    void prepareForPrinting();
};

} // namespace core
