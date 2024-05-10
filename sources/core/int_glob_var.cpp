#include "int_glob_var.hpp"

core::IntGlobVar::IntGlobVar() noexcept
    : IntGlobVar(0, nullptr)
{
}

core::IntGlobVar::IntGlobVar(int aValue, FPIntGlobVarToInt aParser) noexcept
    : mValue(aValue), mParser(aParser)
{
}

//--------------------------------------------------------------------------------

core::IntGlobVar::IntGlobVar(IntGlobVar& other) noexcept
    : mValue(int(other.mValue)), mParser(other.mParser)
{
}

core::IntGlobVar&
core::IntGlobVar::operator=(IntGlobVar& other) noexcept

{
    mValue  = int(other.mValue);
    mParser = other.mParser;
    return *this;
}

//--------------------------------------------------------------------------------
// TODO: use copy
core::IntGlobVar::IntGlobVar(IntGlobVar&& other) noexcept
    : mValue(int(other.mValue)), mParser(other.mParser)
{
}

// TODO: use copy
core::IntGlobVar&
core::IntGlobVar::operator=(IntGlobVar&& other) noexcept

{
    mValue  = int(other.mValue);
    mParser = other.mParser;
    return *this;
}
