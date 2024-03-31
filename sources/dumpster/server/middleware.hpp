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
        const UserData* mUser;
    };

    void before_handle(crow::request& req, crow::response& res, context& ctx);
    void after_handle(crow::request& req, crow::response& res, context& ctx);
};

} // namespace serv

#endif // !MIDDLEWARE_HPP
