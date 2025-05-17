#ifndef TEX_TABLE_HPP
#define TEX_TABLE_HPP

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "domain/holy_trinity.hpp"
#include "domain/to_string.hpp"

#include "tex_base.hpp"

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

class TexTable : public TexBase
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

    TexTable(const std::vector<Column>& aSettings,
             std::unordered_map<str::String, std::vector<str::String>>*
                 aVariables = nullptr) noexcept;
    TexTable(const std::vector<str::String>& aData,
             std::unordered_map<str::String, std::vector<str::String>>*
                 aVariables = nullptr) noexcept;
    HOLY_TRINITY_NOCOPY(TexTable);

    void fromRawData(const std::vector<str::String>& aData) noexcept;
    str::String get() const noexcept;

    template <typename... Args>
    void pushBack(Args&&... args) noexcept
    {
        // if (mCurColumn++ != 1) mData += "& ";
        // mData += dom::toString(std::forward<T>(aData));
        // mData += " ";

        // mData += aArgs[0] == '$' ? getVariable(aArgs) : aArgs;
        // (void)(mData += (getVariable(std::forward<Args>(args)), 0), ...);
        mData += (getVariable(std::forward<Args>(args)) + ...);
        // mData.push_back('&');
        //(void)(temp.emplace_back(toString(std::forward<Args>(args)), 0), ...);
    }

    template <typename T>
    void setWithCount(
        T&& aData,
        ColumnType aType,
        int aSize                    = 0,
        ColumnBorders aColumnBorders = ColumnBorders::Both) noexcept
    {
        if (aSize == 0) aSize = mSize;

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

    void add(const char* aData) noexcept;
    void newLine(int aFrom = 1, int aTo = 0) noexcept;
    void finish() noexcept;

private:
    int mSize;
    int mCurColumn;
    str::String mData;

    static std::unordered_map<ColumnType, str::String> gPosition;
};

}; // namespace tex

#endif // !TEX_TABLE_HPP
