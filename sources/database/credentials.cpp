#include "credentials.hpp"

#include <cstring>

TABLE_REGISTER_CPP(data, Credentials)

#define COPY_CRED_FIELD(field_name) \
    strncpy(field_name, a_##field_name, sizeof(field_name));

data::Credentials::Credentials(const char* a_name,
                               const char* a_user,
                               const char* a_password,
                               const char* a_hostaddr,
                               const char* a_port,
                               const char* a_shame) noexcept
{
    COPY_CRED_FIELD(name);
    COPY_CRED_FIELD(user);
    COPY_CRED_FIELD(password);
    COPY_CRED_FIELD(hostaddr);
    COPY_CRED_FIELD(port);
    COPY_CRED_FIELD(shame);
}

// void
// data::Credentials::setDefault(std::vector<std::string>& a_credentials)
// noexcept

//     : Credentials("template1", "postgres", "127.0.0.1", "5432", "public")
// {
// }

data::Credentials::Credentials(
    const std::vector<std::string_view>& a_credentials_array) noexcept
    : Credentials(a_credentials_array[0].data(),
                  a_credentials_array[1].data(),
                  a_credentials_array[2].data(),
                  a_credentials_array[3].data(),
                  a_credentials_array[4].data(),
                  a_credentials_array[5].data())
{
}

#define ADD_CRED(name) \
    result += name;    \
    result.push_back('$');

std::string
data::Credentials::getCombined() noexcept
{
    std::string result;
    ADD_CRED(name);
    ADD_CRED(user);
    ADD_CRED(password);
    ADD_CRED(hostaddr);
    ADD_CRED(port);
    ADD_CRED(shame);
    return result;
}
