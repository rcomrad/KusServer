#ifndef POST_PLAN_HANDLER_HPP
#define POST_PLAN_HANDLER_HPP

//--------------------------------------------------------------------------------

#include "crow.h"
#include "post_handler.hpp"

//--------------------------------------------------------------------------------

namespace post
{
class PlanHandler : protected PostHandler
{
public:
    static crow::json::wvalue rawDataHandler(data::RawData& aData) noexcept;
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_PLAN_HANDLER_HPP
