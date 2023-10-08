#ifndef GET_QUESTION_HANDLER_HPP
#define GET_QUESTION_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <unordered_map>

#include "database/connection_manager.hpp"

#include "get_handler.hpp"

//--------------------------------------------------------------------------------

namespace get
{
class QuestionHandler : public GetHandler
{
public:
    static crow::json::wvalue process(int aQuestionID, int aUserId) noexcept;

private:
    std::unordered_map<int, crow::json::wvalue> mQuestions;

    QuestionHandler() noexcept;
    static QuestionHandler& getInstance() noexcept;

    crow::json::wvalue getQuestion(int aQuestionID) const noexcept;
    crow::json::wvalue loadQuestion(int aQuestionID) const noexcept;
};
} // namespace get

//--------------------------------------------------------------------------------

#endif // !GET_QUESTION_HANDLER_HPP
