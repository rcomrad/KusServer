#pragma once

//--------------------------------------------------------------------------------

#include "kernel/framework/module/module.hpp"
#include "kernel/utility/common/holy_trinity.hpp"
#include "kernel/utility/kernel/string/slicer.hpp"

#include "token.hpp"

//--------------------------------------------------------------------------------

namespace serv
{
class Server : public core::Module
{
public:
    HOLY_TRINITY_SINGLETON(Server);
    ~Server() override = default;

    bool loopBody() noexcept override;
    void commandSetup() const noexcept override;
    void variableSetup() const noexcept override;

private:
    Server() noexcept;
};

} // namespace serv

//--------------------------------------------------------------------------------
