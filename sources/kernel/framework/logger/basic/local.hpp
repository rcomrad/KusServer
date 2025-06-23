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

#define LOGGER_REDIRECT(name) core::LocalLogger::getLogger().redirect(name)
