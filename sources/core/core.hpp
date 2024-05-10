#pragma once

//--------------------------------------------------------------------------------

#include <thread>
#include <unordered_map>

#include "domain/holy_trinity.hpp"

#include "string/kus_string.hpp"

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

    std::unordered_map<str::string, std::thread> mApps;
};
} // namespace core

//------------------------------------------------------------------------------
