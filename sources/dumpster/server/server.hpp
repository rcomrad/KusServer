#ifndef SERVER_HPP
#define SERVER_HPP

#include "crow/middlewares/cors.h"

#include "crow.h"
#include "middleware.hpp"

namespace serv
{
class Server
{
public:
    Server() noexcept;
    static const serv::Middleware::context& getContext(
        const crow::request& aReq) noexcept;

private:
    static crow::App<crow::CORSHandler, serv::Middleware> mApp;
};
} // namespace serv

#endif // !SERVER_HPP
