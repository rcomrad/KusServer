#pragma once

//--------------------------------------------------------------------------------

#include "core/command/command_extend.hpp"

//--------------------------------------------------------------------------------

namespace serv
{

class Token
{
public:
    COMMAND_HANDLER(tokenCommandHandler);

#define ENUM_NAME Status
#define VAR_FILE  "server/token_var.inc"
#include "core/variable/var_unpack.inc"
};

} // namespace serv

//--------------------------------------------------------------------------------
