#ifndef CORE_HPP
#define CORE_HPP

//--------------------------------------------------------------------------------

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
    Core() noexcept;
    ~Core() = default;

    Core(const Core& other) noexcept            = default;
    Core& operator=(const Core& other) noexcept = default;

    Core(Core&& other) noexcept            = default;
    Core& operator=(Core&& other) noexcept = default;

    void run(const std::vector<std::string>& argv) noexcept;

    // static data::DBSettings mDBS;
    // static void databaseSettingsInit() noexcept;
    void remakeDatabase();
    void populate();

private:
    std::map<std::string, std::thread> mApps;

    void serverThread() noexcept;
    void testerThread() noexcept;
    void createDatabaseFromFile(std::string aFileName) noexcept;
    void populateDatabaseFromFile(std::string aFileName) noexcept;
    void createEnvironment() noexcept;
    void deleteEnvironment() noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !CORE_HPP
