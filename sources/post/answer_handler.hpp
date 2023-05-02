#ifndef POST_ANSWER_HANDLER_HPP
#define POST_ANSWER_HANDLER_HPP

#include "core/program_state.hpp"

#include "post_handler.hpp"

namespace post
{
class AnswerHandler : public PostHandler
{
public:
    static crow::json::wvalue process(PostRequest<data::Answer>& aReq) noexcept;

private:
    static core::ProgramState& mProgramState;
    static const int ANSWER_FNAME_SIZE = 12;
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !POST_ANSWER_HANDLER_HPP
