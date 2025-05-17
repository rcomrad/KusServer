#pragma once

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

#include <string.h>

#define __FILENAME__ \
    (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOCAL_CONTEXT                                                          \
    core::Context                                                              \
    {                                                                          \
        .file_name = __FILENAME__, .func_name = __func__, .line_num = __LINE__ \
    }

#define DECLARE_LOCAL_CONTEXT core::Context context_local = LOCAL_CONTEXT

//------------------------------------------------------------------------------
