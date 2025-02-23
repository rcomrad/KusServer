#pragma once

//--------------------------------------------------------------------------------

#include "crow/middlewares/cors.h"

#include "crow.h"

//--------------------------------------------------------------------------------

namespace serv
{
class CROWServer
{
public:
    CROWServer();

private:
    void initializeRouts();
    static crow::App<crow::CORSHandler> mApp;
};
} // namespace serv

//--------------------------------------------------------------------------------
