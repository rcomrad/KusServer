#pragma once

#include "crow.h"

namespace server
{

class Middleware
{
public:
    struct context
    {
    };
    void before_handle(crow::request& req, crow::response& res, context& ctx);
    void after_handle(crow::request& req, crow::response& res, context& ctx);
};

} // namespace server
