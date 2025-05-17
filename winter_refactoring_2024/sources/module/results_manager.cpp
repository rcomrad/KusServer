#include "results_manager.hpp"

#include "database/connection_manager.hpp"

#include "domain/date_time.hpp"
#include "domain/time_handler.hpp"
#include "domain/url_wrapper.hpp"
#include "domain/variable_storage.hpp"

#include "text_data/file.hpp"
#include "text_data/path.hpp"

mod::ResultsManager mod::ResultsManager::mInstance;

mod::ResultsManager::ResultsManager() noexcept : ModuleBase({"get_results"})
{
}

std::string
mod::ResultsManager::doAction(const Command& aCommand) noexcept
{
    return getResults(aCommand.argument);
}

std::string
mod::ResultsManager::getResults(const std::string aValue) noexcept
{
    std::string results;

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

    std::string outputName =
        "results" + dom::TimeHandler::getCurentTime().getAllWSpace() + ".txt";
    text::File::writeData("print", outputName, results);

    return dom::UrlWrapper::toSite("print/" + outputName);
}
