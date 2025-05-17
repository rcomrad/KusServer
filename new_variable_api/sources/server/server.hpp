#pragma once

//--------------------------------------------------------------------------------

#include "core/module/module.hpp"

#include "utility/common/holy_trinity.hpp"
#include "utility/string/slicer.hpp"

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
