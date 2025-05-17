#include "submit_handler.hpp"

#include <boost/date_time/gregorian/gregorian.hpp>

#include "database/connection_manager.hpp"
#include "database/safe_sql_wrapper.hpp"

#include "core/submission_queue.hpp"
#include "domain/variable_storage.hpp"
#include "text_data/path.hpp"

crow::json::wvalue
post::SubmitHandler::process(const crow::request& aReq) noexcept
{
    // TODO: result
    crow::json::wvalue res;
    res["result"] = "ok";

    data::Submission submition;

    crow::multipart::message msg(aReq);
    submition.userID    = std::stoi(msg.get_part_by_name("user_id").body);
    submition.problemID = std::stoi(msg.get_part_by_name("problem_id").body);

    submition.dateVal    = getCurentTime();
    submition.verdict    = "NUN";
    submition.test       = -1;
    submition.sourceName = uploadFile(msg);
    // uploadFile(msg, text::Path::getPathUnsafe("submition"));

    {
        auto connection = data::ConnectionManager::getUserConnection();
        connection.val.update<data::Submission>(submition);
    }

    auto& sub = core::SubmissionQueue::getInstance();
    sub.push(std::move(submition));

    // test::Tester tester(10);
    // tester.run(submition);

    return res;
}

std::string
post::SubmitHandler::getCurentTime() noexcept
{
    boost::posix_time::ptime timeLocal =
        boost::posix_time::second_clock::local_time();

    std::string result;
    result += std::to_string(timeLocal.date().year()) + "-";
    result += std::to_string(timeLocal.date().month()) + "-";
    result += std::to_string(timeLocal.date().day()) + " ";

    result += std::to_string(timeLocal.time_of_day().hours()) + ":";
    result += std::to_string(timeLocal.time_of_day().minutes()) + ":";

    if (timeLocal.time_of_day().seconds() < 10) result += "0";
    result += std::to_string(timeLocal.time_of_day().seconds());

    return result;
}
