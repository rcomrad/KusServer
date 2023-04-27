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
    static crow::json::wvalue rawDataHandler(
        std::vector<std::vector<std::string>>& aData,
        const std::vector<std::vector<std::string>>& aAdditionalInfo =
            {}) noexcept;
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_PLAN_HANDLER_HPP
