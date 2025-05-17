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

    // DataArray(T&& aData)
    // {
    //     emplace_back(std::move(aData));
    // }

    DataArray(const std::vector<std::vector<str::String>>& aRaw)
    {
        loadFromRawData(aRaw);
    }

    str::String getTableName() const
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

    size_t size() const
    {
        return mData.size();
    }

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

    bool loadFromRawData(const std::vector<std::vector<str::String>>& aRaw)
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

    crow::json::wvalue::list getAsJList(
        const std::unordered_set<str::String>& aTurnOff = {}) noexcept
    {
        crow::json::wvalue::list result;
        for (const auto& i : mData)
        {
            result.emplace_back(i.getAsJson(aTurnOff));
        }
        return result;
    }

    str::String getAsInsert(
        const std::unordered_set<str::String>& aTurnOff = {}) noexcept
    {
        str::String result;
        for (const auto& i : mData)
        {
            result += i.getAsInsert();
            result.push_back(',');
        }
        if (!result.empty()) result.pop_back();
        return result;
    }

    // str::String getAsUpdate(
    //     const std::unordered_set<str::String>& aTurnOff = {}) noexcept
    // {
    //     str::String result;
    //     for (const auto& i : mData)
    //     {
    //         result += i.getAsUpdate();
    //         result.push_back(',');
    //     }
    //     return result;
    // }

private:
    std::vector<T> mData;
};

} // namespace data

//--------------------------------------------------------------------------------

#endif // !DATA_ARRAY_HPP
