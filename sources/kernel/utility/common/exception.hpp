#pragma once

#include <format>
#include <stdexcept>

#include "kernel/framework/logging/logging.hpp"

#define THROW(...)                                     \
    {                                                  \
        std::string message(std::format(__VA_ARGS__)); \
        LOG_ERROR("%s", message);                      \
        throw std::runtime_error(message);             \
    }
