#pragma once

//--------------------------------------------------------------------------------

#include "kernel/framework/command/command_extend.hpp"

//--------------------------------------------------------------------------------

namespace serv
{

class Token
{
public:
    COMMAND_HANDLER(tokenCommandHandler);

#define ENUM_NAME Status
#define VAR_FILE  "server/token_var.inc"
#include "kernel/framework/variable/var_unpack.inc"
};

} // namespace serv

//--------------------------------------------------------------------------------
