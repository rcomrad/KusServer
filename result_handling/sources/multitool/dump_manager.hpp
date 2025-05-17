#ifndef DUMP_MANAGER_HPP
#define DUMP_MANAGER_HPP

//--------------------------------------------------------------------------------

#include <crow.h>
#include <optional>
#include <string>
#include <vector>

//--------------------------------------------------------------------------------

namespace mult
{
class DumpManager
{
public:
    static std::string process(const crow::request& aReq) noexcept;

    static std::optional<std::string> dumpAsFile(
        const std::vector<std::string>& aTableNames = {}) noexcept;
    static std::string dumpAsString(
        const std::vector<std::string>& aTableNames = {}) noexcept;

    static std::optional<std::string> makeSaveFile() noexcept;

private:
    static std::vector<std::string> getDatabaseTableNames() noexcept;
};
} // namespace mult

//--------------------------------------------------------------------------------

#endif // !DUMP_MANAGER_HPP
