#ifndef CORE_HPP
#define CORE_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "domain/holy_trinity.hpp"

#include "module_base.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class Core : public ModuleBase
{
public:
    HOLY_TRINITY_SINGLE(Core);
    static Core& getInstance() noexcept;

    void run() noexcept;

protected:
    std::string doAction() noexcept override;

private:
    Core() noexcept;

    bool mKillFlag;

    std::unordered_map<std::string, std::thread> mApps;

    void start() noexcept;
    void serverThread() noexcept;
    void testerThread() noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !CORE_HPP
