#pragma once

#include "kernel/framework/module/include_me.hpp"

//-----------

#include "crow/middlewares/cors.h"

#include "crow.h"
#include "middleware.hpp"

namespace server
{

class ServerModule : public core::Module
{
public:
    ServerModule();

protected:
    void initialize() override;

private:
    crow::App<crow::CORSHandler, Middleware> mApp;
};

} // namespace server
