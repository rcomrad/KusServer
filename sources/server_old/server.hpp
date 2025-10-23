#pragma once

//--------------------------------------------------------------------------------

#include "kernel/framework/module/module.hpp"
#include "crow.h"

//--------------------------------------------------------------------------------

namespace serv
{
class Server : public core::Module
{
public:
    static Server& getInstance();
    
    bool loopBody() noexcept override;

    void commandSetup() const noexcept override;
    void variableSetup() const noexcept override;

private:
    crow::SimpleApp app; 
    bool running = false;
};

} // namespace serv

//--------------------------------------------------------------------------------
