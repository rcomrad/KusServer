#ifndef CORE_HPP
#define CORE_HPP

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
    static void setup() noexcept;
    static void run() noexcept;

private:
    bool mAppIsTurnedOn;

    //--------------------------------------------------------------------------

    Core() noexcept;
    HOLY_TRINITY_SINGLE(Core);
    static Core& getInstance() noexcept;

    //--------------------------------------------------------------------------

    void setupNonstatic() noexcept;
    void runNonstatic() noexcept;

    //--------------------------------------------------------------------------

    std::unordered_map<str::string, std::thread> mApps;
};
} // namespace core

//------------------------------------------------------------------------------

#endif // !CORE_HPP
