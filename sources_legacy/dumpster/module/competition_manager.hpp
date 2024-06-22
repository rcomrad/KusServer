#ifndef COMPETITION_MANAGER_HPP
#define COMPETITION_MANAGER_HPP

//--------------------------------------------------------------------------------

#include <string>

#include "module_base.hpp"

//--------------------------------------------------------------------------------

namespace mod
{
class CompetitionManager : public ModuleBase
{
protected:
    std::string doAction(const Command& aComman) noexcept override;

private:
    static CompetitionManager mInstance;
    CompetitionManager() noexcept;

    static std::string userComp(const std::string aValue) noexcept;
};
} // namespace mod

//--------------------------------------------------------------------------------

#endif // !COMPETITION_MANAGER_HPP
