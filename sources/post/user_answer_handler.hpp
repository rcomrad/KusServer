#ifndef POST_USER_ANSWER_HANDLER_HPP
#define POST_USER_ANSWER_HANDLER_HPP

#include "core/program_state.hpp"

#include "post_handler.hpp"

namespace post
{
class UserAnswerHandler : public PostHandler
{
public:
    static crow::json::wvalue process(const crow::request& aReq);

private:
    static core::ProgramState& mProgramState;
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_USER_ANSWER_HANDLER_HPP
