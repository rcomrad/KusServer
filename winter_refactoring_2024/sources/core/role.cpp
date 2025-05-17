#include "role.hpp"

#include "database/connection_manager.hpp"

#include "text_data/parser.hpp"

#include "domain/variable_storage.hpp"

//--------------------------------------------------------------------------------

core::Role::Role() noexcept
{
    auto flag = dom::VariableStorage::touchFlag("bad_db_flag");
    if (!flag)
    {
        loadRoles();

        // TODO: call only after database remake
        resetFormRoleIDs();
    }
}

core::Role&
core::Role::getInstance() noexcept
{
    static Role instance;
    return instance;
}

void
core::Role::loadRoles() noexcept
{
    mRoleToInt.clear();
    mIntToRole.clear();

    data::DataArray<data::Role> table;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        table           = connection.val.getDataArray<data::Role>();
    }

    for (auto& rol : table)
    {
        mIntToRole.emplace_back(std::move(rol.name));
    }
    for (int i = 0; i < mIntToRole.size(); ++i)
    {
        mRoleToInt[mIntToRole[i]] = 1 << i;
    }
}

void
core::Role::resetFormRoleIDs() const noexcept
{
    int adminRole = 0;
    auto it       = mRoleToInt.find("admin");
    if (it != mRoleToInt.end())
    {
        adminRole = it->second;
    }

    auto connection = data::ConnectionManager::getUserConnection();
    auto forms      = connection.val.getDataArray<data::Form>();
    for (auto& i : forms)
    {
        i.roleID = getRoleID(i.roleStr, ",") | adminRole;
    }
    connection.val.write(forms);
}

//--------------------------------------------------------------------------------

int
core::Role::getRoleID(
    const std::unordered_set<std::string>& aRoleNames) noexcept
{
    return getInstance().getRoleIDNonstatic(aRoleNames);
}

int
core::Role::getRoleID(const std::vector<std::string>& aRoleNames) noexcept
{
    std::unordered_set<std::string> s(aRoleNames.begin(), aRoleNames.end());
    return getRoleID(s);
}

int
core::Role::getRoleID(const std::string& aRoleNames,
                      const std::string& aDelimiter) noexcept
{
    auto roles = text::Parser::slice(
        aRoleNames, (aDelimiter.size() == 0) ? " \t\n,;"s : aDelimiter);
    return getRoleID(roles);
}

//--------------------------------------------------------------------------------

std::unordered_set<std::string>
core::Role::getRoles(int aRoleID) noexcept
{
    return getInstance().getRolesNonstatic(aRoleID);
}

//--------------------------------------------------------------------------------

int
core::Role::getRoleIDNonstatic(
    const std::unordered_set<std::string>& aRoleNames) const noexcept
{
    int result = 0;
    for (auto& i : aRoleNames)
    {
        auto it = mRoleToInt.find(i);
        if (it != mRoleToInt.end())
        {
            result |= it->second;
        }
    }
    return result;
}

std::unordered_set<std::string>
core::Role::getRolesNonstatic(int aRoleID) const noexcept
{
    std::unordered_set<std::string> result;
    if (aRoleID > 0)
    {
        for (int i = 0; i < mIntToRole.size(); ++i, aRoleID >>= 1)
        {
            if (aRoleID & 1)
            {
                result.insert(mIntToRole[i]);
            }
        }
    }
    return result;
}
