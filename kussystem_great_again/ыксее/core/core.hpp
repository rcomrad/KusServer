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
    HOLY_TRINITY_SINGLE(Core);

    static void setup() noexcept;
    static void run() noexcept;

private:
    Core() noexcept;
    static Core& getInstance() noexcept;

    void setupNonstatic() noexcept;
    void runNonstatic() noexcept;

    void scanCommand() noexcept;

    std::unordered_map<str::String, std::thread> mApps;
};
} // namespace core

//------------------------------------------------------------------------------
