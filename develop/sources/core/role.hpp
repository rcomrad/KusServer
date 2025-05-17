#ifndef ROLE_HPP
#define ROLE_HPP

//--------------------------------------------------------------------------------

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

//--------------------------------------------------------------------------------

namespace core
{

class Role
{
public:
    static Role& getInstance() noexcept;

    int getRoleID(const std::set<std::string>& aRoleNames) noexcept;
    std::set<std::string> getRoles(int aRoleID) noexcept;

private:
    Role() noexcept;
    void reset() noexcept;

    std::unordered_map<std::string, int> mRoleToInt;
    std::vector<std::string> mIntToRole;
};

} // namespace core

//--------------------------------------------------------------------------------

#endif // !ROLE_HPP
