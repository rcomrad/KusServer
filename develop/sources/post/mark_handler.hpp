#ifndef POST_MARK_HANDLER_HPP
#define POST_MARK_HANDLER_HPP

//--------------------------------------------------------------------------------

#include "crow.h"
#include "post_handler.hpp"

//--------------------------------------------------------------------------------

namespace post
{
class MarkHandler : protected PostHandler
{
public:
    static crow::json::wvalue process(PostRequest<data::Mark>& aReq) noexcept;
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_MARK_HANDLER_HPP
