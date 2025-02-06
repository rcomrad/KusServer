#include "print_type.hpp"

#include <string>
#include <string_view>
#include <unordered_map>

const char*
util::PrintType::process(int arg) noexcept
{
    return "%d";
}

const char*
util::PrintType::process(double arg) noexcept
{
    return "%lf";
}

const char*
util::PrintType::process(const char* arg) noexcept
{
    return "%s";
}

const char*
util::PrintType::process(std::type_index a_type) noexcept
{
    static std::unordered_map<std::type_index, const char*> router = {
        {typeid(int),              "d" },
        {typeid(float),            "f" },
        {typeid(double),           "lf"},
        {typeid(char*),            "s" },
        {typeid(std::string),      "s" },
        {typeid(std::string_view), "s" },
    };
    return router[a_type];
}

const char*
util::PrintType::process(TypeID a_type) noexcept
{
    static std::unordered_map<TypeID, const char*> router = {
        {TypeID::S_INT_32,    "d" },
        {TypeID::U_INT_32,    "d" },
        {TypeID::FLOAT,       "f" },
        {TypeID::DOUBLE,      "lf"},
        {TypeID::CHAR_PTR,    "s" },
        {TypeID::STRING,      "s" },
        {TypeID::STRING_VIEW, "s" },
    };
    return router[a_type];
}
