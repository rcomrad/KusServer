#include "answer_handler.hpp"

#include "domain/date_and_time.hpp"

#include "file_data/file.hpp"
#include "file_data/variable_storage.hpp"

crow::json::wvalue
post::AnswerHandler::process(post::PostRequest<data::Answer>& aReq) noexcept
{
    auto& answer = aReq.data;

    answer.verdict = '?';
    answer.time    = dom::DateAndTime::getCurentTime();
    answer.weight  = -1;

    // crow::multipart::message msg(aReq);
    // submition.back().userID =
    // std::stoi(msg.get_part_by_name("user_id").body);

    if (answer.value.size() < ANSWER_FNAME_SIZE)
    {
        answer.value.push_back('.');
    }
    else
    {
        // TODO: optional
        answer.value =
            file::File::writeData("answer", "x.ans", answer.value).value();
    }

    data::Question question;
    data::Answer oldAnswer;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        question        = connection.val.getData<data::Question>(
            "id=" + data::wrap(answer.questionID));
        oldAnswer = connection.val.getData<data::Answer>(
            "user_id=" + data::wrap(answer.userID) + " AND " +
            "question_id=" + data::wrap(answer.questionID));
    }
    if (oldAnswer.id) answer.id = oldAnswer.id;
    answer.verdict = answer.value == question.juryAnswer ? 'T' : 'F';

    // if
    // (file::VariableStorage::getInstance().getFlagUnsafe("answer_auto_check"))
    // {
    // auto ansTable = connection.val.getData<data::Question>(
    //     "_id = " + data::wrap(table[0].questionID));
    //     auto answer = ansTable[0].juryAnswer;

    // if (answer == table[0].value) table[0].is_correct = 'T';
    // else table[0].is_correct = 'F';
    // }

    // if (mProgramState.checkFlag(core::Flag::TIME_SET))
    // {
    //     table[0].time = dom::DateAndTime::getCurentTime();
    // }
    // else
    // {
    //     table[0].true_time = "NUN";
    // }

    auto connection = data::ConnectionManager::getUserConnection();
    auto res        = connection.val.write(answer);
    return {res};
}
