// #pragma once

// //--------------------------------------------------------------------------------

// #include <map>
// #include <optional>
// #include <unordered_set>

// #include "string/kus_string.hpp"

// #include "read_target.hpp"

// //--------------------------------------------------------------------------------

// namespace fs
// {

// class FileWrite
// {
// public:
//     FileWrite(const str::string& aFileName,
//               const str::string& aFolderName) noexcept;
//     ~FileWrite();

//     void write(const char* format, ...) noexcept;

//     static bool writeData(const std::string& aFileName,
//                           const str::string& aData) noexcept;
//     // static std::optional<str::string> writeData(
//     //     const str::string& aFolderName,
//     //     const str::string& aFileName,
//     //     const str::string& aData) noexcept;

// private:
//     FILE* m_file;
// };

// } // namespace fs

// //--------------------------------------------------------------------------------
