#ifndef CORE_HPP
#define CORE_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "domain/holy_trinity.hpp"

#include "module/module_base.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class Core

{
public:
    static void run() noexcept;

private:
    bool mAppIsTurnedOn;
    static route::RouterNode mRouterNode;

    //----------------------------------------------------------------------------

    Core() noexcept;
    HOLY_TRINITY_SINGLE(Core);
    static Core& getInstance() noexcept;

    //----------------------------------------------------------------------------

    void setup() noexcept;
    void runNonstatic() noexcept;

    //----------------------------------------------------------------------------

    

    std::unordered_map<str::string, std::thread> mApps;

    void start() noexcept;
    void serverThread() noexcept;
    void testerThread() noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !CORE_HPP
