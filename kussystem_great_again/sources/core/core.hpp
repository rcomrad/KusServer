#pragma once

//--------------------------------------------------------------------------------

#include <thread>

#include "kus_standard/hash_map_by_str.hpp"

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

    inline static const char CORE_APP_STORAGE_NAME[] = "CoreStorage";
    kstd::HashMapByStr<CORE_APP_STORAGE_NAME, 200, std::thread> m_apps;
};
} // namespace core

//------------------------------------------------------------------------------
