#ifndef DATA_ARRAY_HPP
#define DATA_ARRAY_HPP

#include "database_wrappers.hpp"

#include "row.hpp"

namespace data
{

template <typename T>
class DataArray
{
public:
    DataArray()
    {
    }

    DataArray(T&& aData)
    {
        emplace_back(std::move(aData));
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

    // int getIndex(const std::string& aName)
    // {
    //     auto it = T::columnNames.find(aName);
    //     int res = -1;
    //     if (it != T::columnNames.end()) return it->second;
    //     return res;
    // }

    // size_t columnCount()
    // {
    //     return T::columnNames.size();
    // }

    // size_t size() const
    // {
    //     return mData.size();
    // }

    size_t empty() const
    {
        return mData.size() == 0;
    }

    //--------------------------------------------------------------------------------

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

    T& back()
    {
        return mData.back();
    }

    auto backRow()
    {
        return Row<T>(T::types, mData.back());
    }

    auto begin()
    {
        return mData.begin();
    }

    // auto begin() const
    // {
    //     return mData.cbegin();
    // }

    auto end()
    {
        return mData.end();
    }

    // auto end() const
    // {
    //     return mData.cend();
    // }

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

    //     bool loadFromRawData(const std::vector<std::vector<std::string>>&
    //     aData)
    //     {
    //         bool result = false;

    //         if (aData.size() != 0 && (aData[0].size() == this->columnCount()
    //         ||
    //                                   aData[0].size() == this->columnCount()
    //                                   - 1))
    //         {
    //             bool hasOffset = this->columnCount() - aData[0].size();
    //             result         = true;

    //             for (auto& i : aData)
    //             {
    //                 bool flag = hasOffset;
    //                 this->emplace_back();
    //                 for (auto& i : this->backRow())
    //                 {
    //                     if (flag)
    //                     {
    //                         flag = false;
    //                     }
    //                     else
    //                     {
    //                         fromString(i.type, i.ptr, i);
    //                     }
    //                 }
    //             }
    //         }

    //         return result;
    //     }

    bool loadFromRawData(const std::vector<std::vector<std::string>>& aRaw)
    {
        bool result = false;

        if (aRaw.size() != 0 && (aRaw[0].size() == T::types.size() ||
                                 aRaw[0].size() == T::types.size() - 1))
        {
            result = true;
            for (auto& i : aRaw)
            {
                emplace_back(T(i));
            }
        }

        return result;
    }

private:
    // std::unordered_map<std::string, uint8_t> mNames;
    // std::vector<data::Type> mTypes;
    std::vector<T> mData;
};

} // namespace data

//--------------------------------------------------------------------------------

#endif // !DATA_ARRAY_HPP
