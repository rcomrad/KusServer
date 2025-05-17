#include "role.hpp"

#include "database/connection_manager.hpp"

#include "file_data/parser.hpp"

#include "variable_storage.hpp"

core::Role::Role() noexcept
{
    // reset();
    auto flag = VariableStorage::touchFlag("bad_db_flag");
    if (!flag)
    {
        loadRoles();
        resetFormRoleIDs();
    }
}

core::Role&
core::Role::getInstance() noexcept
{
    static Role instance;
    return instance;
}

// void
// core::Role::reset() noexcept
// {
//     auto flag = file::VariableStorage::getInstance().getFlag("bad_db_flag");
//     if (!flag.has_value() || flag.has_value() && !flag.value())
//     {
//         loadRoles();
//         resetFormRoleIDs();
//     }
// }

int
core::Role::getRoleID(
    const std::unordered_set<str::String>& aRoleNames) noexcept
{
    return getInstance().getRoleIDNonstatic(aRoleNames);
}

int
core::Role::getRoleID(const std::vector<str::String>& aRoleNames) noexcept
{
    std::unordered_set<str::String> s(aRoleNames.begin(), aRoleNames.end());
    return getRoleID(s);
}

int
core::Role::getRoleID(const char* aRoleNames, const char* aDelimiter) noexcept
{
    auto roles = file::Parser::slice(
        aRoleNames, (aDelimiter.size() == 0) ? " \t\n,;"s : aDelimiter);
    return getRoleID(roles);
}

std::unordered_set<str::String>
core::Role::getRoles(int aRoleID) noexcept
{
    return getInstance().getRolesNonstatic(aRoleID);
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
    auto connection = data::ConnectionManager::getUserConnection();
    auto forms      = connection.val.getDataArray<data::Form>();
    for (auto& i : forms)
    {
        // TODO: use functions
        auto roles = file::Parser::slice(i.roleStr, ","s);
        roles.emplace_back("admin");
        std::unordered_set<str::String> s(roles.begin(), roles.end());
        i.roleID = getRoleIDNonstatic(s);
    }
    connection.val.write(forms);
}

int
core::Role::getRoleIDNonstatic(
    const std::unordered_set<str::String>& aRoleNames) const noexcept
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

std::unordered_set<str::String>
core::Role::getRolesNonstatic(int aRoleID) const noexcept
{
    std::unordered_set<str::String> result;
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
