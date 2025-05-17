#pragma once

//--------------------------------------------------------------------------------

#include <atomic>

//--------------------------------------------------------------------------------
namespace core
{

typedef int (*FPIntGlobVarToInt)(const char*);

struct IntGlobVar
{
    IntGlobVar() noexcept;
    IntGlobVar(int aValue, FPIntGlobVarToInt aParser) noexcept;

    IntGlobVar(IntGlobVar& other) noexcept;
    IntGlobVar& operator=(IntGlobVar& other) noexcept;

    IntGlobVar(IntGlobVar&& other) noexcept;
    IntGlobVar& operator=(IntGlobVar&& other) noexcept;

    std::atomic<int> mValue   = 0;
    FPIntGlobVarToInt mParser = nullptr;
};

} // namespace core

//--------------------------------------------------------------------------------
