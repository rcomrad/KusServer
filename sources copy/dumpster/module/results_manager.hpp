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
    str::String doAction(const Command& aCommand) noexcept override;

private:
    static ResultsManager mInstance;
    ResultsManager() noexcept;

    static str::String getResults(const str::String aValue) noexcept;
};
} // namespace mod

//--------------------------------------------------------------------------------

#endif // !RESULTS_MANAGER_HPP
