#include "tex_table.hpp"

std::unordered_map<tex::ColumnType, std::string> tex::TexTable::gPosition = {
    {tex::ColumnType::Nun,            "" },
    {tex::ColumnType::Left,           "l"},
    {tex::ColumnType::Centr,          "c"},
    {tex::ColumnType::Right,          "r"},
    {tex::ColumnType::IsParagraph,    "" },
    {tex::ColumnType::ParagraphLeft,  "p"},
    {tex::ColumnType::ParagraphCentr, "P"}
};

tex::TexTable::TexTable(const std::vector<Column>& aSettings) noexcept
    : mSize(0), mCurColumn(1)
{
    mData.reserve(2000);
    mData += "\\begin{tabular}{ ";
    mData += "|";
    for (auto& i : aSettings)
    {
        mData += "*{" + std::to_string(i.count) + "}{";
        mData += gPosition[i.type];
        if (i.type > ColumnType::IsParagraph)
        {
            mData += "{";
            mData += std::to_string(i.size);
            mData += "cm}";
        }
        mData += "|}";

        mSize += i.count;
    }
    mData += " }\n";
}

std::string
tex::TexTable::get() const noexcept
{
    return mData;
}

void
tex::TexTable::add(const std::string& aData) noexcept
{
    mData += aData;
}

void
tex::TexTable::newLine(int aFrom, int aTo) noexcept
{
    if (aTo == 0) aTo = mSize;

    mData += "\\\\ \\cline{";
    mData += std::to_string(aFrom);
    mData += "-";
    mData += std::to_string(aTo);
    mData += "}\n";

    mCurColumn = 1;
}

void
tex::TexTable::finish() noexcept
{
    mData += "\\end{tabular}\n";
}
