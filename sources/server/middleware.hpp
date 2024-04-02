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

    bool redirection_flag = true;

    void before_handle(crow::request& req, crow::response& res, context& ctx);
    void after_handle(crow::request& req, crow::response& res, context& ctx);

    void process_comp_question(crow::response& res,
                               serv::UserData user,
                               std::string id);
    void process_comp_user(crow::response& res,
                           serv::UserData user,
                           std::string id);

    void emergency_redirection();

    bool redirection_enabled();
};

} // namespace serv

#endif // !MIDDLEWARE_HPP
