#ifndef SERVER_HPP
#define SERVER_HPP

#include "crow.h"

namespace core
{
struct TokenMiddleware
{
    TokenMiddleware() = default;
    struct context
    {
        context() = default;
    };

    void before_handle(crow::request& req, crow::response& res, context& ctx);
    void after_handle(crow::request& req, crow::response& res, context& ctx);
};

class Server
{
public:
    Server();
};
} // namespace core

#endif // !SERVER_HPP
