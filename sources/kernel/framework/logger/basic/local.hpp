#pragma once

#include "logger.hpp"

namespace core
{

class LocalLogger
{
public:
    static Logger& getLogger() noexcept;
};

} // namespace core

#define LOGGER_INIT(name) core::LocalLogger::getLogger().init(name)
