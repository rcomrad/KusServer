#pragma once

#include "database_wrappers.hpp"

namespace data
{
struct DummyBase : public BaseDataStruct<int, str::String, bool>
{
    int a;
    str::String b;
    bool c;

    void reset() noexcept;

    int getCharCount() const noexcept;
};

using Dummy = UpperDataStruct<DummyBase>;

}; // namespace data
