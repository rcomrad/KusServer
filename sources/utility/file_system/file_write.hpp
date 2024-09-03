#pragma once

//--------------------------------------------------------------------------------

#include <map>
#include <optional>
#include <unordered_set>

#include "core/logging/context.hpp"

#include "string/kus_string.hpp"

#include "read_target.hpp"

//--------------------------------------------------------------------------------

namespace util
{

class FileWrite
{
public:
    FileWrite(const core::Context& a_context,
              const str::string& a_file_name) noexcept;
    ~FileWrite();

    void write(const char* format, ...) noexcept;

private:
    FILE* m_file;
    bool m_is_print_error_msg;
};

} // namespace util

#define FILE_WRITER(name, ...) util::FileWrite name(LOCAL_CONTEXT, __VA_ARGS__);

//--------------------------------------------------------------------------------
