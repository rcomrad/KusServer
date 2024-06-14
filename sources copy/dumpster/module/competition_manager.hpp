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
    str::String doAction(const Command& aComman) noexcept override;

private:
    static CompetitionManager mInstance;
    CompetitionManager() noexcept;

    static str::String userComp(const str::String aValue) noexcept;
};
} // namespace mod

//--------------------------------------------------------------------------------

#endif // !COMPETITION_MANAGER_HPP
