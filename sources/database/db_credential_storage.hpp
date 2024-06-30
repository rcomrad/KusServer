#pragma once

#include <vector>

#include "core/holy_trinity.hpp"
#include "core/types/types.hpp"

namespace data
{

class DBCredentialStorage
{
public:
    struct DBCredentials
    {
        const char* name;
        const char* user;
        const char* password;
        const char* hostaddr;
        const char* port;
        const char* shame;
    };

    enum CredentialType
    {
        NUN,
        ADMIN,
        USER
    };

    HOLY_TRINITY_SINGLETON(DBCredentialStorage);

    SINGL_RET_METHOD(DBCredentials&, getCredentials, (word_t a_credentials_id));
    SINGL_RET_METHOD(word_t, getAdminID, ());

private:
    std::vector<DBCredentials> m_storage;

    DBCredentialStorage() noexcept;
};

} // namespace data
