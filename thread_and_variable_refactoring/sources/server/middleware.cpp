#include "middleware.hpp"

#include "core/variable_storage.hpp"

#include "token_handler.hpp"

void
serv::Middleware::before_handle(crow::request& req,
                                crow::response& res,
                                context& ctx)
{
    while (core::VariableStorage::isLocked())
        ;

    auto user = serv::TokenHandler::process(req);
    if (user.has_value())
    {
        ctx.mUser = user.value();
    }
    else
    {
        res.code = 403;
        res.end();
    }
}

void
serv::Middleware::after_handle(crow::request& req,
                               crow::response& res,
                               context& ctx)
{
}
