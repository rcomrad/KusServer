#ifndef STRUCT_ARRAY_HPP
#define STRUCT_ARRAY_HPP

#include "database_wrappers.hpp"

#include "row.hpp"

namespace data
{

template <typename T>
class StructArray
{
public:
    StructArray()
    {
    }

    StructArray(T&& aData)
    {
        emplace_back(std::move(aData));
    }

    void reset()
    {
        mData.clear();
    }

    std::string getTableName() const
    {
        return T::tableName;
    }

    //--------------------------------------------------------------------------------

    template <typename... Args>
    void emplace_back(Args&&... args)
    {
        mData.emplace_back(std::forward<Args>(args)...);
    }

    void pop_back()
    {
        mData.pop_back();
    }

    void clear()
    {
        mData.clear();
    }

    void reserve(size_t aSize)
    {
        mData.reserve(aSize);
    }

    //--------------------------------------------------------------------------------

    int getIndex(const std::string& aName)
    {
        auto it = T::columnNames.find(aName);
        int res = -1;
        if (it != T::columnNames.end()) return it->second;
        return res;
    }

    // data::Type getType(size_t aNum)
    // {
    //     data::Type res = data::Type::NUN;
    //     if (it != names.end()) return it->second;
    //     return res;
    // }

    // const std::vector<data::Type>& getTypes() const
    // {
    //     return mTypes;
    // }

    size_t columnCount()
    {
        return T::columnNames.size();
    }

    size_t size() const
    {
        return mData.size();
    }

    //--------------------------------------------------------------------------------

    // Cell operator[](size_t num)
    // {
    //     return Cell(mTypes[num], mData[num]);
    // }

    T& operator[](size_t num)
    {
        return mData[num];
    }

    Row<T> getRow(size_t num)
    {
        return Row<T>(T::types, mData[num]);
    }

    //--------------------------------------------------------------------------------

    T& front()
    {
        return mData.front();
    }
    auto frontRow()
    {
        return Row<T>(T::types, mData.front());
    }

    // const T& front() const
    // {
    //     return data.front();
    // }

    T& back()
    {
        return mData.back();
    }

    auto backRow()
    {
        return Row<T>(T::types, mData.back());
    }

    // const T& back() const
    // {
    //     return Row(mTypes, data.back());
    // }

    auto begin()
    {
        return mData.begin();
    }

    auto begin() const
    {
        return mData.cbegin();
    }

    auto end()
    {
        return mData.end();
    }

    auto end() const
    {
        return mData.cend();
    }

    //--------------------------------------------------------------------------------

    void turnOffEmptyColumns()
    {
    }

    void turnOffColumn(const std::string& aColumnName)
    {
        // names[aColumnName] *= -1;
        // mNames.erase(aColumnName);
    }

    //--------------------------------------------------------------------------------

private:
    // std::unordered_map<std::string, uint8_t> mNames;
    // std::vector<data::Type> mTypes;
    std::vector<T> mData;
};

} // namespace data

//--------------------------------------------------------------------------------

#endif // !STRUCT_ARRAY_HPP
