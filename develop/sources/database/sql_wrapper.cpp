#include "sql_wrapper.hpp"

data::SQLWrapper::SQLWrapper(int num)
{
    value = std::to_string(num);
}

data::SQLWrapper::SQLWrapper(const char* str)
{
    value = "\'" + std::move(std::string(str)) + "\'";
}
data::SQLWrapper::SQLWrapper(bool b)
{
    if (b) value = "true";
    else value = "false";
}

data::SQLWrapper::operator std::string&&()
{
    return std::move(value);
}
