#ifndef CORE_HPP
#define CORE_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <thread>
#include <unordered_map>

#include "domain/holy_trinity.hpp"

#include "router/command.hpp"
#include "router/router_node.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class Core
{
public:
    HOLY_TRINITY_SINGLE(Core);
    static Core& getInstance() noexcept;

    //----------------------------------------------------------------------------

    void setup() noexcept;
    void run() noexcept;

    //----------------------------------------------------------------------------

public:
    static std::string doAction(const route::Command& aCommand) noexcept;

private:
    std::string doActionNonstatic(const route::Command& aCommand) noexcept;

    //----------------------------------------------------------------------------

private:
    static route::RouterNode mRouterNode;
    bool mKillFlag;
    std::unordered_map<std::string, std::thread> mApps;

    Core() noexcept;

    void start() noexcept;
    void serverThread() noexcept;
    void testerThread() noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !CORE_HPP
