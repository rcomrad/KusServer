#pragma once

#include <string.h>
#include <string>

// TODO: constexpr

#define __FILENAME__                  \
    (strrchr(__FILE__, '/')           \
         ? strrchr(__FILE__, '/') + 1 \
         : (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__))
