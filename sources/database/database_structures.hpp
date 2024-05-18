#pragma once

#include "database_wrappers.hpp"

namespace data
{
struct DummyBase : public BaseDataStruct<int, str::string, bool>
{
    int a;
    str::string b;
    bool c;

    void reset() noexcept;

    int getCharCount() const noexcept;
};

using Dummy = UpperDataStruct<DummyBase>;

}; // namespace data
