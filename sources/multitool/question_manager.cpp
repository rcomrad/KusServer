#include "question_manager.hpp"

#include "database/connection_manager.hpp"

#include "core/variable_storage.hpp"
#include "file_data/file.hpp"
#include "file_data/path.hpp"

mult::QuestionManager mult::QuestionManager::mInstance;

mult::QuestionManager::QuestionManager() noexcept
    : ModuleBase("question", file::Value::Type::String)
{
}

std::string
mult::QuestionManager::doAction() noexcept
{
    static auto& command = core::VariableStorage::touchWord("question");

    std::string result = "ERROR: no such command!";
    if (command == "load")
    {
        result = loadQuestions();
    }
    else if (command == "retest")
    {
        result = retestQuestions();
    }
    return result;
}

std::string
mult::QuestionManager::loadQuestions() noexcept
{
    auto connection = data::ConnectionManager::getUserConnection();
    // connection.val.drop("question", "id > 0");

    auto hasQ = file::Path::getContentMap(file::Path::getPathUnsafe("question"),
                                          file::Path::FileType::Folder);
    std::map<std::string, std::string> questions;
    questions.insert(hasQ.begin(), hasQ.end());

    for (auto& i : questions)
    {
        data::Question q = connection.val.getData<data::Question>(
            "nickname=\'" + i.first + "\'");

        q.name       = i.first;
        q.nickname   = i.first;
        q.type       = "simpl";
        q.weight     = 1;
        q.juryAnswer = "1";

        auto data = file::File::getWordsMap(
            i.second + "data.txt", file::FileType::File,
            [](char c) { return c == '=' || c == '\n' || c == '\0'; });

        auto ansIt  = data.find("answer");
        auto typeIt = data.find("type");
        auto nameIt = data.find("name");

        if (ansIt != data.end()) q.juryAnswer = ansIt->second;
        if (typeIt != data.end()) q.type = typeIt->second;
        if (nameIt != data.end()) q.name = nameIt->second;

        connection.val.write(q);
    }

    return "?";
}

std::string
mult::QuestionManager::retestQuestions() noexcept
{
    auto connection = data::ConnectionManager::getUserConnection();
    auto temp       = connection.val.getDataArray<data::Question>();
    std::unordered_map<int, data::Question> questions;
    for (auto&& i : temp)
    {
        questions[i.id] = std::move(i);
    }

    auto answers = connection.val.getDataArray<data::Answer>();
    for (auto& a : answers)
    {
        a.verdict = (a.value == questions[a.questionID].juryAnswer) ? "T" : "F";
    }

    connection.val.write(answers);

    return "?";
}
