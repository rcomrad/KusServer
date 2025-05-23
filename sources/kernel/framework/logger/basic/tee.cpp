#include "tee.hpp"

#include "local.hpp"

core::TeeLogger::TeeLogger(std::unique_ptr<char[]>& a_buffer)
{
    LocalLogger::getLogger().pushTeeBuffer(a_buffer);
}

core::TeeLogger::~TeeLogger()
{
    LocalLogger::getLogger().popTeeBuffer();
}