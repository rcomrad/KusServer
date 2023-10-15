#include "results_manager.hpp"

#include "domain/url_wrapper.hpp"

#include "database/connection_manager.hpp"

#include "core/variable_storage.hpp"
#include "file_data/file.hpp"
#include "file_data/path.hpp"

mult::ResultsManager mult::ResultsManager::mInstance;

mult::ResultsManager::ResultsManager() noexcept
    : ModuleBase("result", file::Value::Type::String)
{
}

std::string
mult::ResultsManager::doAction() noexcept
{
    static auto& command = core::VariableStorage::touchWord("result");
    return getResults(command);
}

std::string
mult::ResultsManager::getResults(const std::string aValue) noexcept
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
        results += u.login + " ; ";
        for (auto& q : questions)
        {
            auto answer = connection.val.getData<data::Answer>(
                "user_id = " + data::wrap(u.id) +
                " AND "
                "question_id = " +
                data::wrap(q.id));
            if (answer.id)
            {
                results += answer.verdict + ";";
            }
            else
            {
                results += " ;";
            }
        }
        results += "\n";
    }

    file::File::writeData("print", "results.txt", results);

    return dom::UrlWrapper::toSite("print/results.txt");
}
