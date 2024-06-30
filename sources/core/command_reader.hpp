#pragma once

//--------------------------------------------------------------------------------

#include "module.hpp"
#include "holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class CommandReader : public core::Module
{
public:
    HOLY_TRINITY_SINGLETON(CommandReader);
    CommandReader() noexcept;
    void run() noexcept override;
};
} // namespace core

//--------------------------------------------------------------------------------
