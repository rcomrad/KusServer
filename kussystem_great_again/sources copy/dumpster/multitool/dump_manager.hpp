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
    static str::String process(const crow::request& aReq) noexcept;
    static std::optional<str::String> makeSaveFile() noexcept;
    static str::String makeDump(const char* aCommand,
                                const char* aArgs) noexcept;

protected:
    str::String doAction(const Command& aCommand) noexcept override;

private:
    static DumpManager mInstance;
    DumpManager() noexcept;

    static str::String privateProcess(const char* aCommand,
                                      const char* aArgs) noexcept;

    static str::String dumpAsString(
        const std::vector<str::String>& aTableNames = {}) noexcept;
    static std::optional<str::String> dumpAsFile(
        const std::vector<str::String>& aTableNames = {}) noexcept;
    static str::String dumpAsHTML(
        const std::vector<str::String>& aTableNames = {}) noexcept;

    static std::vector<str::String> getDatabaseTableNames() noexcept;
};
} // namespace mult

//--------------------------------------------------------------------------------

#endif // !DUMP_MANAGER_HPP
