#ifndef CORE_HPP
#define CORE_HPP

//--------------------------------------------------------------------------------

#include <unordered_map>
#include <string>
#include <thread>
#include <vector>

#include "domain/holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class Core
{
public:
    HOLY_TRINITY_SINGLE(Core);
    static Core& getInstance() noexcept;

    void run() noexcept;

private:
    Core() noexcept;

    bool mKillFlag;

    std::unordered_map<std::string, std::thread> mApps;

    void serverThread() noexcept;
    void testerThread() noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !CORE_HPP
