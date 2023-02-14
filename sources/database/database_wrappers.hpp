#ifndef DATABASE_WRAPPERS_HPP
#define DATABASE_WRAPPERS_HPP

//--------------------------------------------------------------------------------

#include <map>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "database/sql_wrapper.hpp"

//--------------------------------------------------------------------------------

namespace data
{
struct ColumnSetting
{
    std::string name;
    std::string type;
    std::string info;

    // For stupid GNU!
    ColumnSetting(std::string aName, std::string aType,
                  std::string aInfo = "") noexcept;
};

struct DBSettings
{
    std::string name;
    std::string user;
    std::string password;
    std::string shame;
};

enum class Type
{
    NUN,
    INT,
    BOOL,
    CHARS,
    STRING
};

template <size_t size>
struct BaseDataStruct
{
    void* ptrs[size];

    void* operator[](size_t num)
    {
        return ptrs[num];
    }

    // TODO: is it safe?
    // const void const* operator[](size_t num) const
    const void* operator[](size_t num) const
    {
        return ptrs[num];
    }
};

template <typename T>
struct UpperDataStruct : public T
{
    UpperDataStruct() noexcept : T()
    {
        T::reset();
    }
    ~UpperDataStruct() = default;

    UpperDataStruct(const UpperDataStruct& other)            = delete;
    UpperDataStruct& operator=(const UpperDataStruct& other) = delete;

    UpperDataStruct(UpperDataStruct&& other) noexcept : T(other)
    {
        T::reset();
    }
    UpperDataStruct& operator=(UpperDataStruct&& other) noexcept
    {
        T::reset();
        return *this;
    }
};

template <typename T>
struct Table
{
    std::unordered_map<std::string, uint8_t> names;
    std::vector<data::Type> types;
    std::vector<T> data;

    Table()
    {
        reset();
    }

    std::string getTableName() const
    {
        return T::tableName;
    }

    void emplace_back()
    {
        data.emplace_back();
    }

    void clear()
    {
        data.clear();
    }

    void emplace_back(T&& other)
    {
        data.emplace_back(std::move(other));
    }

    size_t getIndex(const std::string& aName)
    {
        auto it    = names.find(aName);
        size_t res = -1;
        if (it != names.end()) return it->second;
        return res;
    }

    T& operator[](size_t num)
    {
        return data[num];
    }

    const T& operator[](size_t num) const
    {
        return data[num];
    }

    void reset()
    {
        types = T::types;
        names = T::columnNames;
    }

    T& back()
    {
        return data.back();
    }

    auto begin()
    {
        return data.begin();
    }

    auto end()
    {
        return data.end();
    }

    auto begin() const
    {
        return data.cbegin();
    }

    auto end() const
    {
        return data.cend();
    }

    size_t columnCount()
    {
        return types.size();
    }

    size_t size() const
    {
        return data.size();
    }

    std::string getCondition(int num = 0) const
    {
        auto strs = makeStrings(num);
        std::string res;
        for (const auto& i : strs) res += i + " AND ";
        res.resize(res.size() - 4);
        return res;
    }

    std::string getString(int num = 0, bool aSkipID = false) const
    {
        auto strs = makeStrings(aSkipID);
        std::string res;
        for (const auto& i : strs) res += i + ", ";
        res.resize(res.size() - 2);
        return res;
    }

    std::vector<std::string> makeStrings(int num, bool aSkipName = false,
                                         bool aSkipID = false) const noexcept
    {
        std::vector<std::string> res(names.size());

        std::string row;
        int id = 0;
        for (const auto& j : names)
        {
            if (aSkipID && j.first == "id")
            {
                continue;
            }

            auto temp = data[num][j.second];
            switch (types[j.second])
            {
                case data::Type::INT:
                    row += wrap(*((int*)temp));
                    break;
                case data::Type::BOOL:
                    row += wrap(*((bool*)temp));
                    break;
                case data::Type::CHARS:
                    row += wrap(*((char*)temp));
                    break;
                case data::Type::STRING:
                    row += wrap(*((std::string*)temp));
                    break;
            }

            if (row != "\'\'" && row != "0")
            {
                if (!aSkipName) row = j.first + " = " + row;
                res[j.second - 1] = std::move(row);
            }
            row.clear();
        }

        while (res.size() && res.back().empty()) res.pop_back();

        // int l = 0, r = 1;
        // while (r < res.size())
        // {
        //     while (l < res.size() && res[l].size() == 0)
        //     {
        //         ++l;
        //     }
        //     r = l + 1;
        //     while (r < res.size() && res[r].size() == 0)
        //     {
        //         ++r;
        //     }
        //     if (l < res.size() && r < res.size())
        //         res[l++] = std::move(res[r++]);
        // }
        // res.resize(l);

        return res;
    }
};

} // namespace data

//--------------------------------------------------------------------------------

#endif // !DATABASE_WRAPPERS_HPP
