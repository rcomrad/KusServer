#pragma once

//--------------------------------------------------------------------------------

#include <thread>
#include <unordered_map>

#include "string/kus_string.hpp"

#include "holy_trinity.hpp"

//------------------------------------------------------------------------------

namespace core
{
class Core
{
public:
    HOLY_TRINITY_SINGLETON(Core);

    SINGL_VOID_METHOD(setup, ());
    SINGL_VOID_METHOD(run, ());
    SINGL_RET_METHOD(bool, isRunning, ());

private:
    Core() noexcept = default;
    void scanCommand() noexcept;
};
} // namespace core

//------------------------------------------------------------------------------
