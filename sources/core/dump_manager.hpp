#ifndef DUMP_MANAGER_HPP
#define DUMP_MANAGER_HPP

//--------------------------------------------------------------------------------

#include <optional>
#include <string>
#include <vector>

//--------------------------------------------------------------------------------

namespace core
{
class DumpManager
{
public:
    static std::optional<std::string> dumpAsFile(
        const std::vector<std::string>& aTableNames = {}) noexcept;
    static std::string dumpAsString(
        const std::vector<std::string>& aTableNames = {}) noexcept;

    static std::optional<std::string> makeSaveFile() noexcept;

private:
    static std::vector<std::string> getDatabaseTableNames() noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !DUMP_MANAGER_HPP
