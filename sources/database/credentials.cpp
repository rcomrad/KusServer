#include "credentials.hpp"

#include <cstring>

data::Credentials::Credentials(const char* name,
                               const char* user,
                               const char* password,
                               const char* hostaddr,
                               const char* port,
                               const char* shame) noexcept
{
    std::memset(m_credentials.combined_str, 0, CREDENTIAL_MEMORY_SIZE);

#define COPY_CRED_FIELD(field_name)                      \
    strncpy(m_credentials.fields.field_name, field_name, \
            sizeof(CredentialsFields::field_name));

    COPY_CRED_FIELD(name);
    COPY_CRED_FIELD(user);
    COPY_CRED_FIELD(password);
    COPY_CRED_FIELD(hostaddr);
    COPY_CRED_FIELD(port);
    COPY_CRED_FIELD(shame);

#undef COPY_CRED_FIELD

    calculateHash();
}

data::Credentials::Credentials(Credentials&& other) noexcept
{
    *this = std::move(other);
}

data::Credentials&
data::Credentials::operator=(Credentials&& other) noexcept
{
    memcpy(m_credentials.combined_str, other.m_credentials.combined_str,
           CREDENTIAL_MEMORY_SIZE);
    return *this;
}

uint64_t
data::Credentials::calculateHash() const noexcept
{
    uint64_t m_hash = 0;
    for (int i = 0; i < CREDENTIAL_MEMORY_SIZE; ++i)
    {
        m_hash += ((uint64_t)m_credentials.combined_str[i]) * 13ULL;
    }
    return m_hash;
}

void
data::Credentials::setDefault(std::vector<std::string>& a_credentials) noexcept
{
    a_credentials.emplace_back("template1");
    a_credentials.emplace_back("postgres");
    a_credentials.emplace_back("127.0.0.1");
    a_credentials.emplace_back("5432");
    a_credentials.emplace_back("public");

    swap(a_credentials[0], a_credentials[1]);
    swap(a_credentials[1], a_credentials[2]);
}

void
data::Credentials::printData(char** a_ptr,
                             core::TablePrintHelper& a_table) const noexcept
{
    a_table.printData(a_ptr, m_credentials.fields.name);
    a_table.printData(a_ptr, m_credentials.fields.user);
    a_table.printData(a_ptr, m_credentials.fields.password);
    a_table.printData(a_ptr, m_credentials.fields.hostaddr);
    a_table.printData(a_ptr, m_credentials.fields.port);
    a_table.printData(a_ptr, m_credentials.fields.shame);
}

void
data::Credentials::configurateTable(core::TablePrintHelper& a_table) noexcept
{
    PUSH_BASIC_COLUMN(CredentialsFields, name);
    PUSH_BASIC_COLUMN(CredentialsFields, user);
    PUSH_BASIC_COLUMN(CredentialsFields, password);
    PUSH_BASIC_COLUMN(CredentialsFields, hostaddr);
    PUSH_BASIC_COLUMN(CredentialsFields, port);
    PUSH_BASIC_COLUMN(CredentialsFields, shame);
}

void
data::Credentials::dumpCredentialsToFIle(fs::FileWrite& a_file) const noexcept
{
    a_file.write("%s %s %s %s %s %s\n", m_credentials.fields.name,
                 m_credentials.fields.user, m_credentials.fields.password,
                 m_credentials.fields.hostaddr, m_credentials.fields.port,
                 m_credentials.fields.shame);
}
