#ifndef DUMP_MANAGER_HPP
#define DUMP_MANAGER_HPP

//--------------------------------------------------------------------------------

#include <crow.h>
#include <optional>
#include <string>
#include <vector>

#include "module/module_base.hpp"

//--------------------------------------------------------------------------------

namespace mult
{
class DumpManager : public mod::ModuleBase
{
public:
    static std::string process(const crow::request& aReq) noexcept;
    static std::optional<std::string> makeSaveFile() noexcept;
    static std::string makeDump(const std::string& aCommand,
                                const std::string& aArgs) noexcept;

protected:
    std::string doAction(const Command& aCommand) noexcept override;

private:
    static DumpManager mInstance;
    DumpManager() noexcept;

    static std::string privateProcess(const std::string& aCommand,
                                      const std::string& aArgs) noexcept;

    static std::string dumpAsString(
        const std::vector<std::string>& aTableNames = {}) noexcept;
    static std::optional<std::string> dumpAsFile(
        const std::vector<std::string>& aTableNames = {}) noexcept;
    static std::string dumpAsHTML(
        const std::vector<std::string>& aTableNames = {}) noexcept;

    static std::vector<std::string> getDatabaseTableNames() noexcept;
};
} // namespace mult

//--------------------------------------------------------------------------------

#endif // !DUMP_MANAGER_HPP
