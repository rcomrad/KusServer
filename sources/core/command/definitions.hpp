#pragma once

//--------------------------------------------------------------------------------

#include <memory>

//--------------------------------------------------------------------------------

namespace core
{

using FP_ResultCallback = void (*)(std::unique_ptr<char[]>&&, void*) noexcept;

static inline std::string CALLBACK_VOLUME_COMMAND_HANDLER = "command";

} // namespace core

//--------------------------------------------------------------------------------
