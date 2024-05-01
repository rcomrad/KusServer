#include "read_result.hpp"

fs::ReadResult::operator str::string() noexcept
{
    str::string res;
    if (mIsDataInRef)
    {
        res = *mDataRef;
    }
    else
    {
        res = std::move(mData);
    }
}
