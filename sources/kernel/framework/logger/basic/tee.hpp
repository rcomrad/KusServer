#pragma once

#include <memory>

//------------------------------------------------------------------------------

namespace core
{

class TeeLogger
{
public:
    TeeLogger(std::unique_ptr<char[]>& a_buffer);
    ~TeeLogger();
};

} // namespace core
