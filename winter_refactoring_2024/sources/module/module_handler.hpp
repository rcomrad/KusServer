#ifndef MODULE_HANDLER_HPP
#define MODULE_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "text_data/value.hpp"

#include "module_base.hpp"

//--------------------------------------------------------------------------------

namespace mod
{
class ModuleHandler
{
public:
    static void run() noexcept;
    static std::string processCommand(const std::string& aCommand,
                                      const std::string& aArgument) noexcept;
    static void applyCommand(const std::string& aCommand,
                             const std::string& aArgument) noexcept;

    static void addCommandHandler(const std::string& aCommand,
                                  ModuleBase* aPtr) noexcept;
    static bool hasCommand(const std::string& aCommand) noexcept;

private:
    ModuleHandler() noexcept = default;
    static ModuleHandler& getInstance() noexcept;

    std::mutex mCommandMutex;
    std::vector<ModuleBase::Command> mCommands;

    std::mutex mResultMutex;
    std::unordered_map<int, std::string> mResults;

    std::unordered_map<std::string, ModuleBase*> mModules;

    void executeCommand(int aResultNumber,
                        const ModuleBase::Command& aCommand) noexcept;

    void runNonstatic() noexcept;
    int applyCommandNonstatic(const std::string& aCommand,
                              const std::string& aArgument,
                              bool aSaveResult) noexcept;
    std::string processCommandNonstatic(const std::string& aCommand,
                                        const std::string& aArgument) noexcept;
};
} // namespace mod

//--------------------------------------------------------------------------------

#endif // !MODULE_HANDLER_HPP
