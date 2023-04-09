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
    ColumnSetting(std::string aName,
                  std::string aType,
                  std::string aInfo = "") noexcept;
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
class Table
{
public:
    Table(int aSize = 0)
    {
        reset();
        data.resize(aSize);
    }

    std::string getTableName() const
    {
        return T::tableName;
    }

    void emplace_back()
    {
        data.emplace_back();
    }

    void emplace_back(T&& other)
    {
        data.emplace_back(std::move(other));
    }

    void pop_back()
    {
        data.pop_back();
    }

    void clear()
    {
        data.clear();
    }

    void reserve(int aSize)
    {
        data.reserve(aSize);
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

    std::vector<std::string> makeStrings(int num,
                                         bool aSkipName = false,
                                         bool aSkipID   = false) const noexcept
    {
        std::vector<std::string> res(names.size());

        std::string row;
        int id = 0;
        for (const auto& j : names)
        {
            if (aSkipID && j.first == "id" && j.second == 0)
            {
                continue;
            }

            auto temp = data[num][j.second];
            char bb   = 0;
            switch (types[j.second])
            {
                case data::Type::INT:
                    row += wrap(*((int*)temp));
                    break;
                case data::Type::BOOL:
                    bb = *((char*)temp);
                    if (bb != -1) row += wrap(bool(bb));
                    break;
                case data::Type::CHARS:
                    row += wrap(*((char*)temp));
                    break;
                case data::Type::STRING:
                    row += wrap(*((std::string*)temp));
                    break;
            }

            if (!row.empty() && row != "\'\'" && row != "0")
            {
                if (!aSkipName) row = j.first + " = " + row;
                res[j.second] = std::move(row);
            }
            row.clear();
        }

        int l = 0;
        while (!res[l].empty()) l++;
        int r = l + 1;

        while (r < res.size())
        {
            while (r < res.size() && res[r].empty()) ++r;
            if (!(r < res.size())) break;

            res[l] = std::move(res[r]);
            ++l;
        }

        res.resize(l);

        return res;
    }

    void turnOffEmptyColumns()
    {
    }

    void turnOffColumn(const std::string& aColumnName)
    {
        // names[aColumnName] *= -1;
        names.erase(aColumnName);
    }

    //--------------------------------------------------------------------------------

    bool loadFromRawData(const std::vector<std::vector<std::string>>& aData)
    {
        bool result = false;

        if (aData.size() != 0 && aData[0].size() != 0 &&
            (aData[0].size() == names.size() ||
             aData[0].size() == names.size() - 1))
        {
            result     = true;
            int offset = names.size() - aData[0].size();

            for (auto& i : aData)
            {
                emplace_back();
                for (int j = 0; j < i.size(); ++j)
                {
                    int ind = offset + j;
                    switch (types[ind])
                    {
                        case data::Type::INT:
                            *(int*)back()[ind] = std::stoi(i[j]);
                            break;
                        case data::Type::BOOL:
                            *(bool*)back()[ind] = i[j] == "true";
                            break;
                        case data::Type::STRING:
                            *(std::string*)back()[ind] = i[j];
                            break;
                    }
                }
            }
        }

        return result;
    }

    //--------------------------------------------------------------------------------

public:
    std::unordered_map<std::string, uint8_t> names;
    std::vector<data::Type> types;
    std::vector<T> data;
};

} // namespace data

//--------------------------------------------------------------------------------

#endif // !DATABASE_WRAPPERS_HPP
