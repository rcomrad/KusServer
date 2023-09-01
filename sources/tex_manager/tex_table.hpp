#ifndef TEX_FILE_HPP
#define TEX_FILE_HPP

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "domain/holy_trinity.hpp"
#include "domain/to_string.hpp"

namespace tex
{
enum class ColumnType
{
    Nun,
    Left,
    Centr,
    Right,
    IsParagraph,
    ParagraphLeft,
    ParagraphCentr
};

enum class ColumnBorders
{
    Nun,
    Left,
    Right,
    Both
};

class TexTable
{
public:
    struct Column
    {

        // enum class Size
        // {
        //     Nun,
        //     CM,
        //     MM
        // };

        ColumnType type;
        float size;
        int count = 1;
    };

    TexTable(const std::vector<Column>& aSettings) noexcept;
    HOLY_TRINITY_NOCOPY(TexTable);

    std::string get() const noexcept;

    template <typename T>
    void pushBack(T&& aData) noexcept
    {
        if (mCurColumn++ != 1) mData += "& ";
        mData += dom::toString(std::forward<T>(aData));
        mData += " ";
    }

    template <typename T>
    void setWithCount(
        T&& aData,
        ColumnType aType,
        int aSize,
        ColumnBorders aColumnBorders = ColumnBorders::Both) noexcept
    {
        if (mCurColumn != 1) mData += "& ";
        mCurColumn += aSize;

        mData += "\\multicolumn{";
        mData += std::to_string(aSize);
        mData += "}{";
        if (int(aColumnBorders) & int(ColumnBorders::Left)) mData += "|";
        mData += gPosition[aType];
        if (int(aColumnBorders) & int(ColumnBorders::Right)) mData += "|";
        mData += "}{";
        mData += dom::toString(std::forward<T>(aData));
        mData += "}\n";
    }

    template <typename T>
    void setWithRange(
        T&& aData,
        ColumnType aType,
        int aFrom,
        ColumnBorders aColumnBorders = ColumnBorders::Both) noexcept
    {
        setWithRange(aData, aType, aFrom, 0, aColumnBorders);
    }

    template <typename T>
    void setWithRange(
        T&& aData,
        ColumnType aType,
        int aFrom,
        int aTo,
        ColumnBorders aColumnBorders = ColumnBorders::Both) noexcept
    {
        if (aTo == 0) aTo = mSize;
        else ++aTo;
        while (aFrom > mCurColumn) pushBack("");
        setWithCount(aData, aType, aTo - aFrom, aColumnBorders);
    }

    void add(const std::string& aData) noexcept;
    void newLine(int aFrom = 1, int aTo = 0) noexcept;
    void finish() noexcept;

private:
    int mSize;
    int mCurColumn;
    std::string mData;

    static std::unordered_map<ColumnType, std::string> gPosition;
};

}; // namespace tex

#endif // !TEX_FILE_HPP
