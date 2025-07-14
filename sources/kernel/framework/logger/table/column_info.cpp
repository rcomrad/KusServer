#include "column_info.hpp"

#include <cmath>
#include <regex>
#include <utility>

//------------------------------------------------------------------------------

core::ColumnInfo&
core::ColumnInfo::setName(const std::string& a_name)
{
    m_name        = a_name;
    m_sizes.at(0) = m_name.size();
    return *this;
}

core::ColumnInfo&
core::ColumnInfo::setSeparator(char a_separator)
{
    m_separator = a_separator;
    return *this;
}

//------------------------------------------------------------------------------

void
core::ColumnInfo::alignmentSwitch(Alignment a_alignment)
{
    auto align = std::exchange(m_alignment, Alignment::NUN);

    if (align == Alignment::RIGHT) alignmentRight();
    if (align == Alignment::MIDDLE) alignmentMiddle();
    if (align == Alignment::LEFT) alignmentLeft();
}

core::ColumnInfo&
core::ColumnInfo::alignmentRight()
{
    if (m_alignment == Alignment::RIGHT) return *this;
    prepareFormat(Alignment::RIGHT, "%s%*x");
    return *this;
}

core::ColumnInfo&
core::ColumnInfo::alignmentMiddle()
{
    if (m_alignment == Alignment::MIDDLE) return *this;
    m_alignment = Alignment::MIDDLE;
    m_format =
        std::regex_replace("%*s%s%x%*s", std::regex("x"), m_type_specifier);
    return *this;
}

core::ColumnInfo&
core::ColumnInfo::alignmentLeft()
{
    if (m_alignment == Alignment::LEFT) return *this;
    prepareFormat(Alignment::LEFT, "%s%-*x");
    return *this;
}

//------------------------------------------------------------------------------

core::ColumnInfo&
core::ColumnInfo::turnOn()
{
    m_is_printed = true;
    return *this;
}

core::ColumnInfo&
core::ColumnInfo::turnOff()
{
    m_is_printed = false;
    return *this;
}
//------------------------------------------------------------------------------

core::ColumnInfo&
core::ColumnInfo::addPrefix(const char* a_prefix)
{
    m_prefix = a_prefix;
    return *this;
}

core::ColumnInfo&
core::ColumnInfo::setDefault(const char* a_default)
{
    m_default = a_default;
    return *this;
}

//------------------------------------------------------------------------------

void
core::ColumnInfo::prepareFormat(Alignment a_alignment, const char* a_format)
{
    m_alignment = a_alignment;
    m_format = std::regex_replace(a_format, std::regex("x"), m_type_specifier);
    m_format = " " + m_format + " %c";
}

int
core::ColumnInfo::getWidth()
{
    if (!m_is_printed) return 0;

    *m_width =
        std::max(*m_width, *std::max_element(m_sizes.begin(), m_sizes.end()) +
                               2 + 1 + int(strlen(m_prefix)));
    *m_width = std::max(*m_width,
                        2 + 1 + int(strlen(m_prefix)) + int(strlen(m_default)));
    return *m_width;
}

void
core::ColumnInfo::pass(char** a_buffer)
{
    if (!m_is_printed) return;

    *a_buffer += sprintf(*a_buffer, " %*s %c", *m_width - 3, "", m_separator);
}

//------------------------------------------------------------------------------
