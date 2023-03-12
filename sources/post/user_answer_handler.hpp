#ifndef USER_ANSWER_HANDLER_HPP
#define USER_ANSWER_HANDLER_HPP

#include "core/program_state.hpp"

#include "post_handler.hpp"

namespace post
{
class UserAnswerHandler : public PostHandler
{
public:
    static crow::json::wvalue process(const crow::request& aReq,
                                      data::DatabaseQuery& aDBQ);

private:
    static core::ProgramState& mProgramState;
};
} // namespace post

//--------------------------------------------------------------------------------

#endif // !USER_ANSWER_HANDLER_HPP
