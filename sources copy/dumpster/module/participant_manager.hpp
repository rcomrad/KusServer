#ifndef PARTICIPANT_MANAGER_HPP
#define PARTICIPANT_MANAGER_HPP

//--------------------------------------------------------------------------------

#include <string>

#include "module_base.hpp"

//--------------------------------------------------------------------------------

namespace mod
{
class PaticipantManager : public ModuleBase
{
protected:
    std::string doAction(const Command& aComman) noexcept override;

private:
    static PaticipantManager mInstance;
    PaticipantManager() noexcept;

    static std::string userComp(const std::string aValue) noexcept;
};
} // namespace mod

//--------------------------------------------------------------------------------

#endif // !PARTICIPANT_MANAGER_HPP
