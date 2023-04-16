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

} // namespace data

//--------------------------------------------------------------------------------

#endif // !DATABASE_WRAPPERS_HPP
