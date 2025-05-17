#include "tex_table.hpp"

#include <algorithm>

#include "file_data/parser.hpp"

std::unordered_map<tex::ColumnType, str::String> tex::TexTable::gPosition = {
    {tex::ColumnType::Nun,            "" },
    {tex::ColumnType::Left,           "l"},
    {tex::ColumnType::Centr,          "c"},
    {tex::ColumnType::Right,          "r"},
    {tex::ColumnType::IsParagraph,    "" },
    {tex::ColumnType::ParagraphLeft,  "p"},
    {tex::ColumnType::ParagraphCentr, "P"}
};

tex::TexTable::TexTable(
    const std::vector<Column>& aSettings,
    std::unordered_map<str::String, std::vector<str::String>>*
        aVariables) noexcept
    : TexBase(aVariables), mSize(0), mCurColumn(1)
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

tex::TexTable::TexTable(
    const std::vector<str::String>& aData,
    std::unordered_map<str::String, std::vector<str::String>>*
        aVariables) noexcept
    : TexBase(aVariables), mSize(0), mCurColumn(1)
{
    fromRawData(aData);
}

void
tex::TexTable::fromRawData(const std::vector<str::String>& aData) noexcept
{
    mData += "\\begin{tabular}{ " + aData[1] + "}\n";
    std::replace(mData.begin(), mData.end(), 'R', 'p');
    std::replace(mData.begin(), mData.end(), 'C', 'P');

    for (int i = 2; i < aData.size(); ++i)
    {
        if (aData[i][0] == '\\')
        {
            auto parts = file::Parser::slice(aData[i], " ", "\\");
            if (parts.size() < 2) mData += "\\\\ \\hline";
            else mData += "\\\\ \\cline{" + parts[0] + "-" + parts[1] + "}";
        }
        else
        {
            auto parts = file::Parser::slice(aData[i], ";");
            for (auto& j : parts)
            {
                if (j == "-") pushBack(" ");
                else if (j[0] != '[') pushBack(j);
                else
                {
                    auto blocks = file::Parser::slice(j, ",", "[]");
                    mData += "\\multicolumn";

                    std::replace(blocks[1].begin(), blocks[1].end(), 'R', 'p');
                    std::replace(blocks[1].begin(), blocks[1].end(), 'C', 'P');

                    // if (block.size() == 2) mData += "{" + mSize + "}";
                    for (auto& k : blocks) pushBack("{", k, "}");
                    mData += " ";
                }
                mData.push_back('&');
            }
            mData.pop_back();
        }
        mData += "\n";
    }
    // mData += "\\end{tabular}\n";
}

str::String
tex::TexTable::get() const noexcept
{
    return mData;
}

void
tex::TexTable::add(const char* aData) noexcept
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
