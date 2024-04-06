#ifndef RESULTS_MANAGER_HPP
#define RESULTS_MANAGER_HPP

//--------------------------------------------------------------------------------

#include <string>

#include "module_base.hpp"

//--------------------------------------------------------------------------------

namespace mod
{
class ResultsManager : public ModuleBase
{
protected:
    std::string doAction(const Command& aCommand) noexcept override;

private:
    static ResultsManager mInstance;
    ResultsManager() noexcept;

    static std::string getResults(const std::string aValue) noexcept;
};
} // namespace mod

//--------------------------------------------------------------------------------

#endif // !RESULTS_MANAGER_HPP
