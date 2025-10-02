#include "middleware.hpp"

namespace server
{

void
Middleware::before_handle(crow::request& req, crow::response& res, context& ctx)
{
}

void
Middleware::after_handle(crow::request& req, crow::response& res, context& ctx)
{
}

} // namespace server
