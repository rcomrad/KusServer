#pragma once

//--------------------------------------------------------------------------------

#include "holy_trinity.hpp"
#include "module.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class CommandReader : public core::Module
{
public:
    HOLY_TRINITY_SINGLETON(CommandReader);
    CommandReader() noexcept;
    void run() noexcept override;

private:
    static void stdoutOutput(const char* a_buff) noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------
