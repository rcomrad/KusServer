#ifndef CORE_HPP
#define CORE_HPP

//--------------------------------------------------------------------------------

#include <atomic>
#include <map>
#include <string>
#include <thread>
#include <vector>

//--------------------------------------------------------------------------------

namespace core
{
class Core
{
public:
    static Core& getInstance() noexcept;

    Core(const Core& other) noexcept            = default;
    Core& operator=(const Core& other) noexcept = default;

    Core(Core&& other) noexcept            = default;
    Core& operator=(Core&& other) noexcept = default;

    void run() noexcept;

    // static data::DBSettings mDBS;
    // static void databaseSettingsInit() noexcept;
    void remakeDatabase() noexcept;
    void populate() noexcept;

    void kill() noexcept;

private:
    Core() noexcept;
    ~Core() = default;

    std::map<std::string, std::thread> mApps;

    void serverThread() noexcept;
    void testerThread() noexcept;
    void createDatabaseFromFile(std::string aFileName) noexcept;
    // void populateDatabaseFromFile(std::string aFileName) noexcept;
    void createEnvironment() noexcept;
    // void deleteEnvironment() noexcept;

    std::atomic<bool> mKillFlag;
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !CORE_HPP
