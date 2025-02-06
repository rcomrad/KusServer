#include <stdexcept>

#include "kernel/framework/logging/logging.hpp"

#define TRY_BLOCK(expression, phase, on_error)                            \
    try                                                                   \
    {                                                                     \
        expression;                                                       \
    }                                                                     \
    catch (const std::exception& e)                                       \
    {                                                                     \
        LOG_ERROR("Unknown exception in '%s' module during %s phase: %s", \
                  getName(), phase, e.what());                            \
        on_error;                                                         \
    }                                                                     \
    catch (...)                                                           \
    {                                                                     \
        LOG_ERROR("Unknown exception in '%s' module during %s phase.",    \
                  getName(), phase);                                      \
        on_error;                                                         \
    }
