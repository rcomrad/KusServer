#ifndef RESULTS_MANAGER_HPP
#define RESULTS_MANAGER_HPP

//--------------------------------------------------------------------------------

#include <string>

#include "core/module_base.hpp"

//--------------------------------------------------------------------------------

namespace mult
{
class ResultsManager : public core::ModuleBase
{
protected:
    std::string doAction() noexcept override;

private:
    static ResultsManager mInstance;
    ResultsManager() noexcept;

    static std::string getResults(const std::string aValue) noexcept;
};
} // namespace mult

//--------------------------------------------------------------------------------

#endif // !RESULTS_MANAGER_HPP
