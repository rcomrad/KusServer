#ifndef MIDDLEWARE_HPP
#define MIDDLEWARE_HPP

#include "crow.h"
#include "user_data.hpp"

namespace serv
{
struct Middleware
{
    Middleware() = default;
    struct context
    {
        const UserData const* mUser;
    };

    void before_handle(crow::request& req, crow::response& res, context& ctx);
    void after_handle(crow::request& req, crow::response& res, context& ctx);
};

class Server
{
public:
    Server();
};
} // namespace serv

#endif // !MIDDLEWARE_HPP
