#include "submit_handler.hpp"

#include <boost/date_time/gregorian/gregorian.hpp>

#include "domain/path.hpp"

#include "database/database_query.hpp"

crow::json::wvalue
post::SubmitHandler::process(const crow::request& aReq) noexcept
{
    // TODO: result
    crow::json::wvalue res;

    data::Table<data::Submission> submition;
    submition.emplace_back();

    crow::multipart::message msg(aReq);
    submition.back().user_id = std::stoi(msg.get_part_by_name("user_id").body);
    submition.back().problem_id =
        std::stoi(msg.get_part_by_name("problem_id").body);

    submition.back().date_val = getCurentTime();
    submition.back().verdict  = "NUN";
    submition.back().test     = -1;
    submition.back().file_path =
        uploadFile(msg, dom::Path::getPath("submition").value());

    data::DatabaseQuery dbq(data::DatabaseQuery::UserType::USER);
    dbq.update<data::Submission>(submition);

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
