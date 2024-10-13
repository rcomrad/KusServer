#include "evaluate.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "utility/string/parser.hpp"

int
to_int(const std::string_view& a_str)
{
    return std::stoi(std::string(a_str));
}

int
to_double(const std::string_view& a_str)
{
    return std::stod(std::string(a_str));
}

struct Answer
{
    int id;
    int user_id;
    int question_id;
    std::string time;
    char verdict;
    double weight;
    std::string value;

    Answer()
    {
    }
    Answer(const std::vector<std::string_view>& a_data)
    {
        id          = to_int(a_data[0]);
        user_id     = to_int(a_data[1]);
        question_id = to_int(a_data[2]);
        time        = a_data[3];
        verdict     = a_data[4][0];
        weight      = to_double(a_data[5]);
        value       = a_data[6];
    }
};

struct Question
{
    int id;
    std::string name;
    std::string nickname;
    std::string type;
    double weight;
    std::string jury_answer;

    Question()
    {
    }
    Question(const std::vector<std::string_view>& a_data)
    {
        id          = to_int(a_data[0]);
        name        = a_data[1];
        nickname    = a_data[2];
        type        = a_data[3];
        weight      = to_double(a_data[4]);
        jury_answer = a_data[5];
    }
};

void
olymp::Evaluate::processResults(core::CommandExtend& a_command) noexcept
{
    CMD_ASSERT(argCount(1).noVars());
    auto& file_name = a_command.arguments[0];

    std::ifstream file(file_name.data());
    std::string data;
    std::getline(file, data, '\0');
    auto words = util::Parser::getWords(data, ";\t\"\'");

    std::vector<Answer> answers;
    std::vector<Question> question;

    int num = 0;
    for (auto& i : words)
    {
        if (i.empty()) continue;

        if (i[0] == "answer")
        {
            num = 1;
            continue;
        }
        else if (i[0] == "question")
        {
            num = 2;
            continue;
        }
        else if (i[0] == "END")
        {
            num = 0;
        }

        switch (num)
        {
            case 1:
                answers.emplace_back(i);
                break;
            case 2:
                question.emplace_back(i);
                break;
        }
    }

    for (auto& i : answers)
    {
        if (i.value == "нет" || i.value == "неверно" || i.value == "НЕВЕРНО" ||
            i.value == "неверно " || i.value == "Неверно" || i.value == "НЕТ" ||
            i.value == " нет" || i.value == "нет " || i.value == "НЕТ " ||
            i.value == "НКЕТ" || i.value == "Нет " || i.value == "НЕT" ||
            i.value == " НЕТ" || i.value == "HET" || i.value == "Нет" ||
            i.value == "No" || i.value == "no" || i.value == "väärin" ||
            i.value == "не" || i.value == "väärin " ||
            i.value == "virheellinen")
        {
            i.value = "false";
        }
        if (i.value == "да" || i.value == "верно" || i.value == "ВЕРНО" ||
            i.value == "ДАТ" || i.value == "Д" || i.value == "А" ||
            i.value == "а" || i.value == "ДА" || i.value == "Да" ||
            i.value == "да " || i.value == "ВЕРНО " || i.value == "yes" ||
            i.value == "Yes" || i.value == "Да " || i.value == "ДА " ||
            i.value == " ДА" || i.value == "Верно" || i.value == "oikein" ||
            i.value == "oikea")
        {
            i.value = "true";
        }
    }

    std::vector<std::set<std::string>> wrong(question.size());
    for (auto& i : answers)
    {
        int id = i.question_id - 1;
        if (i.value != question[id].jury_answer)
        {
            wrong[id].insert(i.value);
        }
    }

    int cnt = 1;
    for (auto& i : wrong)
    {
        std::cout << cnt++ << " ";
        for (auto& j : i)
        {
            std::cout << "[" << j << "]" << " ";
        }
        std::cout << std::endl;
    }
    //     for (auto& i : answers)
    //     {
    //         std::cout << i.value << std::endl;
    //     }
}
