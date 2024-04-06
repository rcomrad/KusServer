#ifndef ROW_HPP
#define ROW_HPP

#include "database_wrappers.hpp"

namespace data
{

template <typename T>
class Row
{
private:
    struct Cell
    {
        Type type;
        void* ptr;
        int num;
    };

    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = Cell;
        using pointer           = Cell;
        using reference         = Cell;

        Iterator(const std::vector<data::Type>& aTypes, T& aRow, int aNum)
            : mTypes(aTypes), mRow(aRow), mNum(aNum)
        {
        }

        reference operator*() const
        {
            return Cell(mTypes[mNum], mRow[mNum], mNum);
        }
        pointer operator->()
        {
            return Cell(mTypes[mNum], mRow[mNum], mNum);
        }
        Iterator& operator++()
        {
            mNum++;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++mNum;
            return tmp;
        }
        friend bool operator==(const Iterator& a, const Iterator& b)
        {
            return a.mNum == b.mNum;
        };
        friend bool operator!=(const Iterator& a, const Iterator& b)
        {
            return a.mNum != b.mNum;
        };

        operator int() const
        {
            return mNum;
        }

    private:
        int mNum;
        const std::vector<data::Type>& mTypes;
        T& mRow;
    };

public:
    Row(const std::vector<data::Type>& aTypes, T& aRow)
        : mTypes(aTypes), mRow(aRow)
    {
    }

    void* ptr(size_t num)
    {
        return mRow[num];
    }
    Type type(size_t num) const
    {
        return mTypes[num];
    }
    size_t size(size_t num) const
    {
        return mTypes.size();
    }

    Cell operator[](size_t num) const
    {
        return Cell(mTypes[num], mRow[num]);
    }

    Iterator begin()
    {
        return Iterator(mTypes, mRow, 0);
    }
    Iterator end()
    {
        return Iterator(mTypes, mRow, mTypes.size());
    }

private:
    const std::vector<data::Type>& mTypes;
    T& mRow;
};

} // namespace data

//--------------------------------------------------------------------------------

#endif // !ROW_HPP
