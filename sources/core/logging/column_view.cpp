#include "column_view.hpp"

#include <typeindex>
#include <unordered_map>

#include "core/logging/logging.hpp"

namespace
{

std::unordered_map<std::type_index, std::string>
getSuffixMap() noexcept
{
    // TODO: types format
    // TODO: remove const by templates
    std::unordered_map<std::type_index, std::string> result;
    result[std::type_index(typeid(int))]         = "d";
    result[std::type_index(typeid(size_t))]      = "u";
    result[std::type_index(typeid(char*))]       = "s";
    result[std::type_index(typeid(const char*))] = "s";
    return result;
}

std::string
getSuffix(const std::type_info& a_type)
{
    std::string result = "";
    // TODO: static? (static upwards)
    auto suffix_map = getSuffixMap();
    auto it         = suffix_map.find(std::type_index(a_type));
    if (it != suffix_map.end())
    {
        result = it->second;
    }
    else
    {
        LOG_ERROR("Unknown type with name '%s' specified for table print",
                  std::type_index(a_type).name());
    }
    return result;
}

} // namespace

core::ColumnView::ColumnView(const std::type_info& a_type,
                             size_t a_size,
                             const std::string& a_name) noexcept
    : size(std::max(a_size, a_name.size())),
      name(a_name),
      format(getSuffix(a_type))
{
}

core::BasicView::BasicView(const std::type_info& a_type,
                           size_t a_mem_size,
                           const std::string& a_var_name) noexcept
    : ColumnView(a_type, a_mem_size, a_var_name)
{
}

core::SizedView::SizedView(const std::type_info& a_type,
                           size_t a_mem_size,
                           const std::string& a_var_name,
                           size_t a_col_size) noexcept
    : ColumnView(a_type, a_col_size, a_var_name)
{
}

core::NamedView::NamedView(const std::type_info& a_type,
                           size_t a_mem_size,
                           const std::string& a_var_name,
                           const std::string& a_col_name) noexcept
    : ColumnView(a_type, a_mem_size, a_col_name)
{
}

core::CombinedView::CombinedView(const std::type_info& a_type,
                                 size_t a_mem_size,
                                 const std::string& a_var_name,
                                 size_t a_col_size,
                                 const std::string& a_col_name) noexcept
    : ColumnView(a_type, a_col_size, a_col_name)
{
}
