#ifndef CORE_HPP
#define CORE_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <thread>
#include <vector>

#include "database/database_query.hpp"

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

private:
    std::map<std::string, std::thread> mApps;
    data::DBSettings mAdminDBS;
    data::DBSettings mDBS;

    void serverThread() noexcept;
    void createDatabaseFromFile(std::string aFileName) noexcept;
    void populateDatabaseFromFile(std::string aFileName) noexcept;
    void createEnvironment() noexcept;
    void deleteEnvironment() noexcept;
    void createJournals() noexcept;
    void createPlans() noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !CORE_HPP
