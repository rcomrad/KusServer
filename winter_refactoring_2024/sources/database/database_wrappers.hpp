#ifndef DATABASE_WRAPPERS_HPP
#define DATABASE_WRAPPERS_HPP

//--------------------------------------------------------------------------------

#include <map>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "text_data/to_string.hpp"

#include "crow.h"
#include "sql_wrapper.hpp"

//--------------------------------------------------------------------------------

namespace data
{

enum class Type
{
    NUN,
    INT,
    FLOAT,
    BOOL,
    CHARS,
    STRING
};

struct BaseDataDummy
{
};

template <size_t size>
struct BaseDataStruct : private BaseDataDummy
{
    void* ptrs[size];

    void* operator[](size_t num) noexcept
    {
        return ptrs[num];
    }

    // TODO: is it safe?
    // const void const* operator[](size_t num) const
    const void* operator[](size_t num) const noexcept
    {
        return ptrs[num];
    }

    BaseDataStruct() noexcept = default;
    ~BaseDataStruct()         = default;

    BaseDataStruct(const BaseDataStruct& other)            = delete;
    BaseDataStruct& operator=(const BaseDataStruct& other) = delete;

    BaseDataStruct(BaseDataStruct&& other) noexcept            = default;
    BaseDataStruct& operator=(BaseDataStruct&& other) noexcept = default;
};

template <typename T>
struct UpperDataStruct : public T
{
    UpperDataStruct() noexcept : T()
    {
        T::reset();
    }

    UpperDataStruct(const std::vector<std::string>& aRaw) noexcept : T()
    {
        T::reset();
        setFromRaw(aRaw);
    }

    ~UpperDataStruct() = default;

    UpperDataStruct(const UpperDataStruct& other)            = delete;
    UpperDataStruct& operator=(const UpperDataStruct& other) = delete;

    UpperDataStruct(UpperDataStruct&& other) noexcept : T(std::move(other))
    {
        T::reset();
    }
    UpperDataStruct& operator=(UpperDataStruct&& other) noexcept
    {
        T::operator=(std::move(other));
        T::reset();
        return *this;
    }

    static std::string geName() noexcept
    {
        return T::tableName;
    }

    std::string getAsCondition() const noexcept
    {
        std::string result;
        for (size_t i = 0; i < T::types.size(); ++i)
        {
            auto temp = toString(T::types[i], T::ptrs[i]);
            if (!temp.empty())
            {
                result += T::columnNames[i];
                result.push_back('=');
                result += temp;
                result += " AND "s;
            }
        }
        if (result.size() > 4) result.resize(result.size() - 5);
        return result;
    }

    std::string getAsInsert() const noexcept
    {
        std::string result = "("s;
        for (size_t i = 0; i < T::types.size(); ++i)
        {
            auto temp = toString(T::types[i], T::ptrs[i]);
            if (temp.empty()) temp = "default"s;
            result += temp;
            result.push_back(',');
        }
        if (!result.empty()) result.back() = ')';
        return result;
    }

    std::string getAsUpdate() const noexcept
    {
        std::string result;
        for (size_t i = 1; i < T::types.size(); ++i)
        {
            auto temp = toString(T::types[i], T::ptrs[i]);
            if (!temp.empty())
            {
                result += T::columnNames[i];
                result.push_back('=');
                result += temp;
                result.push_back(',');
            }
        }
        if (!result.empty()) result.pop_back();
        return result;
    }

    std::string getAsDMP() const noexcept
    {
        std::string result;
        for (size_t i = 0; i < T::types.size(); ++i)
        {
            result += toString<text::ToString>(T::types[i], T::ptrs[i]);
            result.push_back(';');
        }
        return result;
    }

    crow::json::wvalue getAsJson(
        const std::unordered_set<std::string>& aTurnOff = {}) const noexcept
    {
        crow::json::wvalue result;
        for (size_t i = 0; i < T::types.size(); ++i)
        {
            if (aTurnOff.count(T::columnNames[i])) continue;
            switch (T::types[i])
            {
                case data::Type::INT:
                    if (*(int*)T::ptrs[i] != 0)
                        result[T::columnNames[i]] = *(int*)T::ptrs[i];
                    break;
                case data::Type::BOOL:
                    if (*(char*)T::ptrs[i] != 0)
                        result[T::columnNames[i]] =
                            bool(*(char*)T::ptrs[i] + 1);
                    break;
                case data::Type::STRING:
                    if (!((std::string*)T::ptrs[i])->empty())
                        result[T::columnNames[i]] = *(std::string*)T::ptrs[i];
                    break;
                case data::Type::FLOAT:
                    if (*(float*)T::ptrs[i] != 0)
                        result[T::columnNames[i]] = *(float*)T::ptrs[i];
                    break;
            }
        }
        return result;
    }

    void setFromJson(const crow::json::rvalue& aReq) noexcept
    {
        for (auto& i : aReq)
        {
            auto it = T::nameToNum.find(i.key());
            if (it != T::nameToNum.end())
            {
                switch (T::types[it->second])
                {
                    case data::Type::INT:
                        *(int*)T::ptrs[it->second] = i.i();
                        break;
                    case data::Type::BOOL:
                        *(char*)T::ptrs[it->second] = i.b() ? 1 : -1;
                        break;
                    case data::Type::STRING:
                        *(std::string*)T::ptrs[it->second] = i.s();
                        break;
                    case data::Type::FLOAT:
                        *(float*)T::ptrs[it->second] = i.d();
                        break;
                }
            }
        }
    }

    void setFromRaw(const std::vector<std::string>& aRaw) noexcept
    {
        size_t offset = T::types.size() - aRaw.size();
        // TODO: check?
        if (offset != 0 && offset != 1) return;
        for (auto& i : aRaw)
        {
            fromString(T::types[offset], T::ptrs[offset], i);
            ++offset;
        }
    }

    // static std::vector<std::string> getNunExample() noexcept
    // {
    //     std::vector<std::string> result(T::types.size());
    //     for (size_t i = 0; i < T::types.size(); ++i)
    //     {
    //         switch (T::types[i])
    //         {
    //             case data::Type::INT:
    //                 types.emplace_back("-1"s);
    //                 break;
    //             case data::Type::BOOL:
    //                 types.emplace_back("-1"s);
    //                 break;
    //             case data::Type::STRING:
    //                 types.emplace_back("NUN"s);
    //                 break;
    //         }
    //     }
    //     return result;
    // }

protected:
    template <typename StrClass = data::SQLWrapper>
    static std::string toString(data::Type aType, void* aPtr) noexcept
    {
        std::string result;
        switch (aType)
        {
            case data::Type::INT:
                if (*((int*)aPtr) != 0)
                    result = StrClass::convert(*((int*)aPtr));
                break;
            case data::Type::BOOL:
                if (*((char*)aPtr) != 0)
                    result = StrClass::convert(bool((*((char*)aPtr)) + 1));
                break;
            case data::Type::STRING:
                if (!((std::string*)aPtr)->empty())
                    result = StrClass::convert(*((std::string*)aPtr));
                break;
            case data::Type::FLOAT:
                if (*((float*)aPtr) != 0)
                    result = StrClass::convert(*((float*)aPtr));
        }
        return result;
    }

    static void fromString(data::Type aType,
                           void* aPtr,
                           const std::string& aData) noexcept
    {
        switch (aType)
        {
            case data::Type::INT:
                *(int*)aPtr = std::stoi(aData);
                break;
            case data::Type::BOOL:
                // TODO: other bool formats
                *(char*)aPtr = aData == "true"s ? 1 : -1;
                break;
            case data::Type::STRING:
                *(std::string*)aPtr = aData;
                break;
            case data::Type::FLOAT:
                *(float*)aPtr = std::stof(aData);
                break;
        }
    }
};

} // namespace data

//--------------------------------------------------------------------------------

#endif // !DATABASE_WRAPPERS_HPP
