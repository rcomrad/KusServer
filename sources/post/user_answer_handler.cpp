#include "user_answer_handler.hpp"

#include "domain/date_and_time.hpp"

core::ProgramState& post::UserAnswerHandler::mProgramState =
    core::ProgramState::getInstance();

crow::json::wvalue
post::UserAnswerHandler::process(const crow::request& aReq)
{
    auto body  = crow::json::load(aReq.body);
    auto table = parseRequest<data::User_answer>(body).table;

    auto connection = data::ConnectionManager::getUserConnection();

    table[0].is_correct = '?';
    if (mProgramState.isCheckAnswersTurnOn())
    {
        auto ansTable = connection.val.getData<data::Question>(
            "id = " + data::wrap(table[0].question_id));
        auto answer = ansTable[0].jury_answer;

        if (answer == table[0].user_answer) table[0].is_correct = 'T';
        else table[0].is_correct = 'F';
    }

    if (mProgramState.isSetTimeTurnOn())
    {
        table[0].true_time = dom::DateAndTime::getCurentTime();
    }
    else
    {
        table[0].true_time = "NUN";
    }

    auto res = connection.val.update(table);
    return {res};
}
