#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "core/logging/table_storage.hpp"

namespace data
{

struct Credentials
{
    char name[10];
    char user[10];
    char password[15];
    char hostaddr[10];
    char port[8];
    char shame[10];

    Credentials(const char* a_name,
                const char* a_user,
                const char* a_password,
                const char* a_hostaddr,
                const char* a_port,
                const char* a_shame) noexcept;

    Credentials(
        const std::vector<std::string_view>& a_credentials_array) noexcept;

    std::string getCombined() noexcept;

private:
    TABLE_REGISTER_HPP(Credentials,
                       .addCol(obj.name,
                               obj.user,
                               obj.password,
                               obj.hostaddr,
                               obj.port,
                               obj.shame));
};

} // namespace data
