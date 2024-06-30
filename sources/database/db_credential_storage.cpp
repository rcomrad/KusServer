#include "db_credential_storage.hpp"

#include "file_system/file_read.hpp"
#include "file_system/read_target.hpp"

data::DBCredentialStorage::DBCredentialStorage() noexcept
{
    auto credential = fs::FileRead::getWords(
        {fs::ReadTarget::FILE_NAME, "db_credentials.txt"});
    for (auto& i : credential)
    {
        // m_storage.emplace_back(credential[0], credential[1], credential[2],
        //                        credential[3], credential[4]);
    }
}

data::DBCredentialStorage::DBCredentials&
data::DBCredentialStorage::getCredentialsNonstatic(
    word_t a_credentials_id) noexcept
{
    return m_storage[a_credentials_id];
}

word_t
data::DBCredentialStorage::getAdminIDNonstatic() noexcept
{
    return 0;
}
