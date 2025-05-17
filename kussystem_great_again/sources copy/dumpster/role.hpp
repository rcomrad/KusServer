#ifndef ROLE_HPP
#define ROLE_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

//--------------------------------------------------------------------------------

namespace core
{

class Role
{
public:
    static Role& getInstance() noexcept;

    static int getRoleID(
        const std::unordered_set<str::String>& aRoleNames) noexcept;
    static int getRoleID(const std::vector<str::String>& aRoleNames) noexcept;
    static int getRoleID(const char* aRoleNames,
                         const char* aDelimiter = "") noexcept;

    static std::unordered_set<str::String> getRoles(int aRoleID) noexcept;

    // void reset() noexcept;

private:
    Role() noexcept;
    void loadRoles() noexcept;
    void resetFormRoleIDs() const noexcept;

    int getRoleIDNonstatic(
        const std::unordered_set<str::String>& aRoleNames) const noexcept;
    std::unordered_set<str::String> getRolesNonstatic(
        int aRoleID) const noexcept;

    std::unordered_map<str::String, int> mRoleToInt;
    std::vector<str::String> mIntToRole;
};

} // namespace core

//--------------------------------------------------------------------------------

#endif // !ROLE_HPP
