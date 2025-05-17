#include "answer_handler.hpp"

#include "domain/date_and_time.hpp"

#include "database/safe_sql_wrapper.hpp"

#include "core/variable_storage.hpp"
#include "file_data/file.hpp"

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

    // if (answer.value.size() < ANSWER_FNAME_SIZE)
    // {
    //     answer.value.push_back('.');
    // }
    // else
    // {
    //     // TODO: optional
    //     answer.value =
    //         file::File::writeData("answer", "x.ans", answer.value).value();
    // }

    data::Question question;
    data::Answer oldAnswer;
    {
        auto connection = data::ConnectionManager::getUserConnection();
        question        = connection.val.getData<data::Question>(
            "id=" + data::safeWrap(answer.questionID));
        oldAnswer = connection.val.getData<data::Answer>(
            "user_id=" + data::safeWrap(answer.userID) + " AND " +
            "question_id=" + data::safeWrap(answer.questionID));
    }
    if (oldAnswer.id) answer.id = oldAnswer.id;
    if (answer.value.size() > 255)
    {
        dom::writeError("Can't write full answer!", answer.value);
        answer.value.resize(255);
    }

    for (auto i : answer.value)
    {
        if (i == '-' || i == ';')
        {
            answer.value.clear();
            break;
        }
    }

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
