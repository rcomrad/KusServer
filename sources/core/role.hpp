#ifndef ROLE_HPP
#define ROLE_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "domain/holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace core
{

class Role
{
public:
    HOLY_TRINITY_SINGLE(Role);
    static Role& getInstance() noexcept;

    //----------------------------------------------------------------------------

    static int getRoleID(
        const std::unordered_set<std::string>& aRoleNames) noexcept;
    static int getRoleID(const std::vector<std::string>& aRoleNames) noexcept;
    static int getRoleID(const std::string& aRoleNames,
                         const std::string& aDelimiter = "") noexcept;

    //----------------------------------------------------------------------------

    static std::unordered_set<std::string> getRoles(int aRoleID) noexcept;

    //----------------------------------------------------------------------------

private:
    std::unordered_map<std::string, int> mRoleToInt;
    std::vector<std::string> mIntToRole;

    //----------------------------------------------------------------------------

    Role() noexcept;
    void loadRoles() noexcept;
    void resetFormRoleIDs() const noexcept;

    //----------------------------------------------------------------------------

    int getRoleIDNonstatic(
        const std::unordered_set<std::string>& aRoleNames) const noexcept;

    std::unordered_set<std::string> getRolesNonstatic(
        int aRoleID) const noexcept;

    //----------------------------------------------------------------------------
};

} // namespace core

//--------------------------------------------------------------------------------

#endif // !ROLE_HPP
