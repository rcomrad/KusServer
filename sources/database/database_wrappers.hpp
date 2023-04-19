#ifndef DATABASE_WRAPPERS_HPP
#define DATABASE_WRAPPERS_HPP

//--------------------------------------------------------------------------------

#include <map>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "database/sql_wrapper.hpp"

#include "crow.h"

//--------------------------------------------------------------------------------

namespace data
{

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

    std::string getAsCondition()
    {
        std::string result;
        for (size_t i = 0; i < T::types.size(); ++i)
        {
            auto temp = toString(T::types[i], T::ptrs[i]);
            if (!temp.empty())
            {
                result += temp + " AND ";
            }
        }
        result.resize(result.size() - 5);
        return result;
    }

    std::string getAsInsert()
    {
        std::string result = "(";
        for (size_t i = 0; i < T::types.size(); ++i)
        {
            auto temp = toString(T::types[i], T::ptrs[i]);
            if (temp.empty()) temp = "default";
            result += temp;
            result.push_back(',');
        }
        result.back() = ')';
        return result;
    }

    std::string getAsUpdate()
    {
        std::string result;
        for (size_t i = 1; i < T::types.size(); ++i)
        {
            auto temp = toString(T::types[i], T::ptrs[i]);
            if (!temp.empty())
            {
                result += T::names[i] + "=" + temp + ",";
            }
        }
        result.pop_back();
        return result;
    }

    void setFromJson(const crow::json::rvalue& aReq) noexcept
    {
        for (auto& i : aReq)
        {
            auto it = T::nameToNum.find(i.key());
            if (it == T::nameToNum.end())
            {
                switch (T::types[it->second])
                {
                    case data::Type::INT:
                        *(int*)T::ptrs[it->second] = i.i();
                        break;
                    case data::Type::BOOL:
                        *(bool*)T::ptrs[it->second] = i.b();
                        break;
                    case data::Type::STRING:
                        *(std::string*)T::ptrs[it->second] = i.s();
                        break;
                }
            }
        }
    }

protected:
    static std::string toString(data::Type aType, void* aPtr)
    {
        std::string result;
        switch (aType)
        {
            case data::Type::INT:
                if (*((int*)aPtr) != 0) result = wrap(*((int*)aPtr));
                break;
            case data::Type::BOOL:
                if (*((char*)aPtr) != -1) result = wrap(bool(*((char*)aPtr)));
                break;
            case data::Type::STRING:
                if (!((std::string*)aPtr)->empty())
                    result = wrap(*((std::string*)aPtr));
                break;
        }
        return result;
    }

    static void fromString(data::Type aType,
                           void* aPtr,
                           const std::string& aData)
    {
        switch (aType)
        {
            case data::Type::INT:
                *(int*)aPtr = std::stoi(aData);
                break;
            case data::Type::BOOL:
                // TODO: other bool formats
                *(bool*)aPtr = aData == "true";
                break;
            case data::Type::STRING:
                *(std::string*)aPtr = aData;
                break;
        }
    }
};

} // namespace data

//--------------------------------------------------------------------------------

#endif // !DATABASE_WRAPPERS_HPP
