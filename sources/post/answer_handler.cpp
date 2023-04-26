#include "answer_handler.hpp"

#include "domain/date_and_time.hpp"

#include "core/program_state.hpp"
#include "file/file.hpp"

core::ProgramState& post::AnswerHandler::mProgramState =
    core::ProgramState::getInstance();

crow::json::wvalue
post::AnswerHandler::process(const crow::request& aReq)
{
    auto body   = crow::json::load(aReq.body);
    auto answer = parseRequest<data::Answer>(body).data;

    answer.verdict = '?';
    answer.time    = dom::DateAndTime::getCurentTime();
    answer.weight  = -1;

    // crow::multipart::message msg(aReq);
    // submition.back().user_id =
    // std::stoi(msg.get_part_by_name("user_id").body);

    if (answer.value.size() < ANSWER_FNAME_SIZE)
    {
        answer.value.push_back('.');
    }
    else
    {
        answer.value = file::File::writeData("answer", "x.ans", answer.value);
    }

    data::Question question;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        question        = connection.val.getData<data::Question>(
            "id=" + data::wrap(answer.question_id));
    }
    answer.verdict = answer.value == question.jury_answer ? 'T' : 'F';

    if (mProgramState.checkFlag(core::Flag::ANS_CHECK))
    {
        // auto ansTable = connection.val.getData<data::Question>(
        //     "id = " + data::wrap(table[0].question_id));
        //     auto answer = ansTable[0].jury_answer;

        // if (answer == table[0].value) table[0].is_correct = 'T';
        // else table[0].is_correct = 'F';
    }

    // if (mProgramState.checkFlag(core::Flag::TIME_SET))
    // {
    //     table[0].time = dom::DateAndTime::getCurentTime();
    // }
    // else
    // {
    //     table[0].true_time = "NUN";
    // }

    auto connection = data::ConnectionManager::getUserConnection();
    auto res        = connection.val.update(answer);
    return {res};
}
