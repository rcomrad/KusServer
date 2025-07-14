#pragma once

#include <concepts>
#include <memory>
#include <unordered_set>

#include "kernel/utility/type/containers/key_getter.hpp"
#include "kernel/utility/type/containers/value_getter.hpp"

#include "local.hpp"

namespace core
{

class TablePrinter;

template <typename T>
concept NumericOrString = std::integral<T> || std::floating_point<T> ||
                          std::convertible_to<T, std::string_view>;

template <typename Container>
concept isTableContainer = requires(Container a_container) {
    { util::ContainerValue::exec(a_container, a_container.cbegin()).print() };
};

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
        std::unordered_set<std::decay_t<decltype(util::ContainerKey::exec(
            a_container, a_container.begin()))>>
            erased_keys;
        addTableConrainer(a_container, erased_keys);
    }

    template <typename Container, typename Key>
    void addTableConrainer(const Container& a_container,
                           const std::unordered_set<Key>& a_erased_keys) const
    {
        using getKey   = util::ContainerKey;
        using getValue = util::ContainerValue;

        if (a_container.size() == 0) return;

        // add column info
        TABLE_INFO.addKey(getKey::exec(a_container, a_container.begin()));
        if constexpr (isTableContainer<Container>)
        {
            getValue::exec(a_container, a_container.cbegin()).print();
        }

        // calculate column width and print data
        for (int i = 0; i < 2; ++i)
        {
            TABLE_INFO.nextStep();
            for (auto it = a_container.cbegin(); it != a_container.cend(); ++it)
            {
                const auto& key   = getKey::exec(a_container, it);
                const auto& value = getValue::exec(a_container, it);
                if (a_erased_keys.count(key)) continue;

                TABLE_INFO.addCell(key);
                if constexpr (isTableContainer<Container>)
                {
                    value.print();
                }
                TABLE_INFO.newLine();
            }
        }

        TABLE_INFO.finish();
    }

    void addSubline() const
    {
        return TABLE_INFO.addSubline();
    }

    template <NumericOrString Data>
    ColumnInfo& addCell(const Data& a_data) const
    {
        return TABLE_INFO.addCell(a_data);
    }

    template <NumericOrString Data>
    ColumnInfo& addCell(int a_parant, const Data& a_data) const
    {
        return TABLE_INFO.addCell(a_parant, a_data);
    }

    void addCell(const TablePrinter* a_row) const
    {
        a_row->print();
    }
    void addCell(const TablePrinter& a_row) const
    {
        a_row.print();
    }

    void noHead() const;
};

} // namespace core
