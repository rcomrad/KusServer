#include "results_manager.hpp"

#include "domain/date_and_time.hpp"
#include "domain/url_wrapper.hpp"

#include "core/variable_storage.hpp"

#include "database/connection_manager.hpp"

#include "file_data/file.hpp"
#include "file_data/path.hpp"

mod::ResultsManager mod::ResultsManager::mInstance;

mod::ResultsManager::ResultsManager() noexcept : ModuleBase({"get_results"})
{
}

str::String
mod::ResultsManager::doAction(const Command& aCommand) noexcept
{
    return getResults(aCommand.argument);
}

str::String
mod::ResultsManager::getResults(const str::String aValue) noexcept
{
    str::String results;

    auto connection   = data::ConnectionManager::getUserConnection();
    auto com_question = connection.val.getDataArray<data::CompetitionQuestion>(
        "competition_id = " + aValue);
    std::vector<data::Question> questions;
    for (auto& i : com_question)
    {
        questions.emplace_back(connection.val.getData<data::Question>(
            "id = " + data::wrap(i.questionID)));
    }

    auto users = connection.val.getDataArray<data::User>();

    for (auto& u : users)
    {
        auto comUser = connection.val.getData<data::CompetitionUser>(
            "competition_id = " + aValue + " AND " +
            "user_id = " + data::wrap(u.id));
        if (!comUser.id) continue;

        results += u.login + " ; ";
        int sum = 0;
        for (auto& q : questions)
        {
            auto answer = connection.val.getData<data::Answer>(
                "user_id = " + data::wrap(u.id) +
                " AND "
                "question_id = " +
                data::wrap(q.id));
            if (answer.weight == -1) answer.weight = 0;

            if (answer.id)
            {
                results += std::to_string(answer.weight);
                // results += "(" + answer.value + "/" + q.juryAnswer + ")";
            }
            results += ";";

            sum += answer.weight;
        }
        results += ";=;" + std::to_string(sum);
        results += "\n";
    }

    str::String outputName =
        "results" + dom::DateAndTime::getCurentTimeSafe() + ".txt";
    file::File::writeData("print", outputName, results);

    return dom::UrlWrapper::toSite("print/" + outputName);
}
