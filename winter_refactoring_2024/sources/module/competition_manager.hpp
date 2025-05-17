#ifndef COMPETITION_MANAGER_HPP
#define COMPETITION_MANAGER_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>

#include "router/command.hpp"
#include "router/router_node.hpp"

//--------------------------------------------------------------------------------

namespace mod
{
class CompetitionManager
{
private:
    static route::RouterNode glRouter;

    static std::string applyCommand(const route::Command& aCommand) noexcept;

    // data::Competition manageCompetition(
    //     const std::unirdered_map<std::string, std::string>& aVariables);

    static std::string userComp(const std::string aValue) noexcept;
};
} // namespace mod

//--------------------------------------------------------------------------------

#endif // !COMPETITION_MANAGER_HPP
