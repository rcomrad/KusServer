#include "role.hpp"

#include "database/connection_manager.hpp"

#include "program_state.hpp"

core::Role::Role() noexcept
{
    auto& state = ProgramState::getInstance();
    if (!state.checkFlag(Flag::NEW_BD)) reset();
}

core::Role&
core::Role::getInstance() noexcept
{
    static Role instance;
    return instance;
}

int
core::Role::getRoleID(const std::set<std::string>& aRoleNames) noexcept
{
    int result = 0;
    for (auto& i : aRoleNames)
    {
        result |= mRoleToInt[i];
    }
    return result;
}

std::set<std::string>
core::Role::getRoles(int aRoleID) noexcept
{
    std::set<std::string> result;
    for (int i = 0; i < mIntToRole.size(); ++i, aRoleID >>= 1)
    {
        if (aRoleID & 1)
        {
            result.insert(mIntToRole[i]);
        }
    }
    return result;
}

void
core::Role::reset() noexcept
{
    mRoleToInt.clear();
    mIntToRole.clear();

    data::Table<data::Role> table;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        table           = connection.val.getData<data::Role>();
    }

    mIntToRole.reserve(table.size());
    for (auto& rol : table)
    {
        mIntToRole.emplace_back(std::move(rol.name));
    }
    for (int i = 0; i < mIntToRole.size(); ++i)
    {
        mRoleToInt[mIntToRole[i]] = 1 << i;
    }
}
