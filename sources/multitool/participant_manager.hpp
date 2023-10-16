#ifndef PARTICIPANT_MANAGER_HPP
#define PARTICIPANT_MANAGER_HPP

//--------------------------------------------------------------------------------

#include <string>

#include "core/module_base.hpp"

//--------------------------------------------------------------------------------

namespace mult
{
class PaticipantManager : public core::ModuleBase
{
protected:
    std::string doAction() noexcept override;

private:
    static PaticipantManager mInstance;
    PaticipantManager() noexcept;

    static std::string userComp(const std::string aValue) noexcept;
};

class CompetitionManager : public core::ModuleBase
{
protected:
    std::string doAction() noexcept override;

private:
    static CompetitionManager mInstance;
    CompetitionManager() noexcept;

    static std::string userComp(const std::string aValue) noexcept;
};
} // namespace mult

//--------------------------------------------------------------------------------

#endif // !PARTICIPANT_MANAGER_HPP
