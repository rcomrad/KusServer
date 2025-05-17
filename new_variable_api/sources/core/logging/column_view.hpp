#pragma once

#include <string>
#include <typeinfo>

#include "utility/type/base.hpp"

namespace core
{

struct ColumnView
{
    ColumnView(const std::type_info& a_type,
               size_t a_size,
               const std::string& a_name) noexcept;

    const size_t size;
    const std::string name;
    const std::string format;
};

struct BasicView : public ColumnView
{
    BasicView(const std::type_info& a_type,
              size_t a_mem_size,
              const std::string& a_var_name) noexcept;
};

struct SizedView : public ColumnView
{
    SizedView(const std::type_info& a_type,
              size_t a_mem_size,
              const std::string& a_var_name,
              size_t a_col_size) noexcept;
};

struct NamedView : public ColumnView
{
    NamedView(const std::type_info& a_type,
              size_t a_mem_size,
              const std::string& a_var_name,
              const std::string& a_col_name) noexcept;
};

struct CombinedView : public ColumnView
{
    CombinedView(const std::type_info& a_type,
                 size_t a_mem_size,
                 const std::string& a_var_name,
                 size_t a_col_size,
                 const std::string& a_col_name) noexcept;
};

#define BASIC_COLUMN(space, var)                                \
    core::BasicView(typeid(std::decay_t<decltype(space::var)>), \
                    sizeof(space::var), #var)
#define SIZED_COLUMN(space, var, size)                          \
    core::SizedView(typeid(std::decay_t<decltype(space::var)>), \
                    sizeof(space::var), #var, size)
#define NAMED_COLUMN(space, var, name)                          \
    core::NamedView(typeid(std::decay_t<decltype(space::var)>), \
                    sizeof(space::var), #var, name)
#define COMBINED_COLUMN(space, var, size, name)                    \
    core::CombinedView(typeid(std::decay_t<decltype(space::var)>), \
                       sizeof(space::var), #var, size, name)

} // namespace core
