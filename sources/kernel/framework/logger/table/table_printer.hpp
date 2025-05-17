#pragma once

#include <memory>

#include "kernel/utility/type/containers/key_getter.hpp"
#include "kernel/utility/type/containers/value_getter.hpp"

#include "local.hpp"

namespace core
{

class TablePrinter
{
public:
    std::unique_ptr<char[]> buildTable() const;
    virtual void print() const = 0;

    ColumnInfo& getKeyInfo() const;

    void setDefaultSeparator(char a_separator) const;

    template <typename Container>
    void addTableConrainer(const Container& a_container) const
    {
        using getKey   = util::ContainerKey;
        using getValue = util::ContainerValue;

        if (a_container.size() == 0) return;

        // add column info
        TABLE_INFO.addKey(getKey::exec(a_container, a_container.begin()));
        getValue::exec(a_container, a_container.cbegin()).print();

        // calculate column width
        TABLE_INFO.nextStep();
        // for (const auto& i : a_container)
        for (auto it = a_container.cbegin(); it != a_container.cend(); ++it)
        {
            const auto key    = getKey::exec(a_container, it);
            const auto& value = getValue::exec(a_container, it);

            TABLE_INFO.addCell(key);
            value.print();
            TABLE_INFO.newLine();
        }

        // print data
        TABLE_INFO.nextStep();
        // for (const auto& i : a_container)
        for (auto it = a_container.cbegin(); it != a_container.cend(); ++it)
        {
            const auto& key   = getKey::exec(a_container, it);
            const auto& value = getValue::exec(a_container, it);

            TABLE_INFO.addCell(key);
            value.print();
            TABLE_INFO.newLine();
        }

        TABLE_INFO.finish();
    }

    void addSubline() const
    {
        return TABLE_INFO.addSubline();
    }

    template <typename Data>
    ColumnInfo& addCell(const Data& a_data) const
    {
        return TABLE_INFO.addCell(a_data);
    }

    template <typename Data>
    ColumnInfo& addCell(ColumnInfo& a_parant, const Data& a_data) const
    {
        return TABLE_INFO.addCell(a_parant, a_data);
    }

    // ColumnInfo& addRow(const TablePrinter& a_data) const
    // {
    //     addCell(a_data);
    // }
};

} // namespace core
