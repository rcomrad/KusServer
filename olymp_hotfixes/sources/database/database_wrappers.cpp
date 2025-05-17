#include "database_wrappers.hpp"

data::ColumnSetting::ColumnSetting(std::string aName,
                                   std::string aType,
                                   std::string aInfo) noexcept
    : name(aName), type(aType), info(aInfo)
{
}
