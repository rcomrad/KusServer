#pragma once

//--------------------------------------------------------------------------------

#include "string/kus_string.hpp"

//--------------------------------------------------------------------------------

namespace fs
{

struct ReadResult
{
    const str::string* mDataRef;
    str::string mData;
    bool mIsDataInRef;

    operator str::string() noexcept;
};

} // namespace fs

//--------------------------------------------------------------------------------
