#pragma once

//------------------------------------------------------------------------------

#include "utility/common/src_path.hpp"

//------------------------------------------------------------------------------

namespace core
{

struct Context
{
    const char* file_name;
    const char* func_name;
    int line_num;
};

} // namespace core

#define LOCAL_CONTEXT                                                          \
    core::Context                                                              \
    {                                                                          \
        .file_name = __FILENAME__, .func_name = __func__, .line_num = __LINE__ \
    }

#define DECLARE_LOCAL_CONTEXT core::Context context_local = LOCAL_CONTEXT

//------------------------------------------------------------------------------
