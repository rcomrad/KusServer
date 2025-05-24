#pragma once

#include <memory>
#include <string>
#include <vector>

#include "kernel/utility/type/print_helpers/caster.hpp"
#include "kernel/utility/type/print_helpers/empty.hpp"
#include "kernel/utility/type/print_helpers/sizer.hpp"
#include "kernel/utility/type/print_helpers/specifier.hpp"

namespace core
{

struct ColumnInfo
{
    enum Alignment
    {
        NUN,
        LEFT,
        MIDDLE,
        RIGHT
    };

public:
    template <typename T>
    ColumnInfo(int a_indx, const T& a_data)
        : m_indx(a_indx),
          m_count(0),
          m_width(std::make_shared<int>(0)),
          m_separator('|'),
          m_alignment(Alignment::RIGHT)
    {
        m_sizes.emplace_back(0);
        setName("---");
        resetType(a_data);
        turnOn();
        addPrefix("");
        setDefault("");
    }

    template <typename T>
    ColumnInfo(int a_indx, ColumnInfo& a_parent, const T& a_data)
        : ColumnInfo(a_indx, a_data)
    {
        m_width = a_parent.m_width;
        m_sizes.pop_back();
        alignmentSwitch(a_parent.m_alignment);
    }

    ColumnInfo& setName(const std::string& a_name);
    ColumnInfo& setSeparator(char a_separator);

    ColumnInfo& alignmentRight();
    ColumnInfo& alignmentMiddle();
    ColumnInfo& alignmentLeft();

    ColumnInfo& turnOn();
    ColumnInfo& turnOff();

    ColumnInfo& addPrefix(const char* a_prefix);
    ColumnInfo& setDefault(const char* a_default);

    template <typename T>
    ColumnInfo& resetType(const T& a_data)
    {
        m_type_specifier = util::PrintSpecifier::exec(a_data);
        alignmentSwitch(m_alignment);
        return *this;
    }

    template <typename T>
    void takeIntoAccount(const T& a_data)
    {
        if (!m_is_printed) return;
        m_sizes.emplace_back(util::PrintSizer::exec(a_data));
    }

    int getWidth();

    void printHead(char** a_buffer)
    {
        if (!m_is_printed) return;

        std::string format("%*s%s%*s");
        int spaces     = getWidth() - m_sizes.at(m_count++);
        int pad_len    = spaces / 2;
        int additional = spaces % 2 ? 0 : 1;
        *a_buffer += sprintf(*a_buffer, format.data(), pad_len - additional, "",
                             m_name.data(), pad_len, "");
        *a_buffer += sprintf(*a_buffer, "%c", m_separator);
    }
    template <typename T>
    void print(char** a_buffer, const T& a_data, bool a_check_flag = true)
    {
        if (!m_is_printed) return;
        if (a_check_flag && util::PrintEmpty::exec(a_data) && m_default[0])
        {
            m_sizes.at(m_count) = strlen(m_default);
            print(a_buffer, m_default, false);
            return;
        }

        if (m_alignment != Alignment::MIDDLE)
        {
            *a_buffer += sprintf(*a_buffer, m_format.data(), m_prefix,
                                 *m_width - 3 - +int(strlen(m_prefix)),
                                 util::PrintCaster::exec(a_data), m_separator);
            m_count++;
        }
        else
        {
            int spaces =
                *m_width - m_sizes.at(m_count++) - +int(strlen(m_prefix));
            int pad_len    = spaces / 2;
            int additional = spaces % 2 ? 0 : 1;
            *a_buffer +=
                sprintf(*a_buffer, m_format.data(), pad_len - additional, "",
                        m_prefix, util::PrintCaster::exec(a_data), pad_len, "");
            *a_buffer += sprintf(*a_buffer, "%c", m_separator);
        }
    }

    void pass(char** a_buffer);

    operator int()
    {
        return m_indx;
    }

private:
    int m_indx;

    int m_count;
    char m_separator;
    std::string m_name;
    Alignment m_alignment;

    std::shared_ptr<int> m_width;
    std::vector<int> m_sizes;

    const char* m_type_specifier;
    std::string m_format;

    bool m_is_printed;

    const char* m_prefix;
    const char* m_default;

    void prepareFormat(Alignment a_alignment, const char* a_format);
    void alignmentSwitch(Alignment a_alignment);
};

} // namespace core
