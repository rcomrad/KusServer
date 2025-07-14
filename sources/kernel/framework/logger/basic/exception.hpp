#pragma once

#include <stdexcept>

#include "local.hpp"
#include "macrosses.hpp"

namespace core
{

class LoggerException : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

} // namespace core

#define THROW(...)                                         \
    {                                                      \
        std::unique_ptr<char[]> msg;                       \
        core::LocalLogger::getLogger().pushTeeBuffer(msg); \
        LOG_EXEPT(__VA_ARGS__);                            \
        throw core::LoggerException(msg.get());            \
    }

#define CATCH(func)                        \
    try                                    \
    {                                      \
        func;                              \
    }                                      \
    catch (const core::LoggerException& e) \
    {                                      \
    }                                      \
    catch (const std::exception& e)        \
    {                                      \
        LOG_EXEPT("%s", e.what());         \
    }                                      \
    catch (...)                            \
    {                                      \
                                           \
        LOG_EXEPT("Unknown exception");    \
    }
