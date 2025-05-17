// #pragma once

// #include <string>
// #include <vector>

// #include "core/logging/table_print_helper.hpp"

// #include "file_system/file_write.hpp"

// #include "utility/type/base.hpp"

// namespace data
// {

// struct CredentialsFields
// {
//     char name[10];
//     char user[10];
//     char password[15];
//     char hostaddr[10];
//     char port[8];
//     char shame[10];
// };
// constexpr auto CREDENTIAL_MEMORY_SIZE = sizeof(CredentialsFields);

// union CredentialsUnion
// {
//     CredentialsFields fields;
//     char combined_str[CREDENTIAL_MEMORY_SIZE] = {0};
// };

// static_assert(CREDENTIAL_MEMORY_SIZE == sizeof(CredentialsUnion),
//               "Database Credentials struct s ill-formed ");

// class Credentials
// {
// public:
//     Credentials(const Credentials&) noexcept            = delete;
//     Credentials& operator=(const Credentials&) noexcept = delete;
//     Credentials(Credentials&& other) noexcept;
//     Credentials& operator=(Credentials&& other) noexcept;

//     Credentials(const char* name,
//                 const char* user,
//                 const char* password,
//                 const char* hostaddr,
//                 const char* port,
//                 const char* shame) noexcept;
//     uint64_t calculateHash() const noexcept;

//     static void setDefault(std::vector<std::string>& a_credentials) noexcept;

//     void printData(char** a_ptr, core::TablePrintHelper& table) const noexcept;
//     static void configurateTable(core::TablePrintHelper& table) noexcept;

//     void dumpCredentialsToFIle(fs::FileWrite& a_file) const noexcept;

//     // TODO: const
//     CredentialsUnion m_credentials;
// };

// } // namespace data
