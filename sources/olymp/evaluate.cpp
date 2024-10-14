#include "evaluate.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "utility/string/parser.hpp"

std::string customTransliterate(const std::string& input, const std::map<char, std::string>& mapping) {
    std::string output;
    for (char ch : input) {
        auto it = mapping.find(ch);
        if (it != mapping.end()) {
            output += it->second; // Append mapped value
        } else {
            output += ch; // Append original character if no mapping found
        }
    }
    return output;
}

int main() {
    // Define your custom mapping
    std::map<char, std::string> mapping = {
        {'А', "A"}, {'Б', "B"}, {'В', "V"}, {'Г', "G"},
        {'Д', "D"}, {'Е', "E"}, {'Ё', "Yo"}, {'Ж', "Zh"},
        {'З', "Z"}, {'И', "I"}, {'Й', "Y"}, {'К', "K"},
        {'Л', "L"}, {'М', "M"}, {'Н', "N"}, {'О', "O"},
        {'П', "P"}, {'Р', "R"}, {'С', "S"}, {'Т', "T"},
        {'У', "U"}, {'Ф', "F"}, {'Х', "Kh"}, {'Ц', "Ts"},
        {'Ч', "Ch"}, {'Ш', "Sh"}, {'Щ', "Shch"}, {'Ъ', ""}, 
        {'Ы', "Y"}, {'Ь', ""}, {'Э', "E"}, {'Ю', "Yu"},
        {'Я', "Ya"}
    };

    std::string input = "Привет"; // Input string in Cyrillic
    std::string output = customTransliterate(input, mapping);

    std::cout << "Original: " << input << std::endl;
    std::cout << "Transliterated: " << output << std::endl;

    return 0;
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

void
setVerdict(Answer& answer, bool verdict)
{
    if (verdict)
    {
        answer.verdict = 'T';
    }
    else
    {
        answer.verdict = 'F';
    }
}

void
boolCheck(const Question& question, Answer& answer)
{
    if (answer.value == "нет" || answer.value == "неверно" ||
        answer.value == "НЕВЕРНО" || answer.value == "неверно " ||
        answer.value == "Неверно" || answer.value == "НЕТ" ||
        answer.value == " нет" || answer.value == "нет " ||
        answer.value == "НЕТ " || answer.value == "НКЕТ" ||
        answer.value == "Нет " || answer.value == "НЕT" ||
        answer.value == " НЕТ" || answer.value == "HET" ||
        answer.value == "Нет" || answer.value == "No" || answer.value == "no" ||
        answer.value == "väärin" || answer.value == "не" ||
        answer.value == "väärin " || answer.value == "virheellinen")
    {
        answer.value = "false";
    }
    if (answer.value == "да" || answer.value == "верно" ||
        answer.value == "ВЕРНО" || answer.value == "ДАТ" ||
        answer.value == "Д" || answer.value == "А" || answer.value == "а" ||
        answer.value == "ДА" || answer.value == "Да" || answer.value == "да " ||
        answer.value == "ВЕРНО " || answer.value == "yes" ||
        answer.value == "Yes" || answer.value == "Да " ||
        answer.value == "ДА " || answer.value == " ДА" ||
        answer.value == "Верно" || answer.value == "oikein" ||
        answer.value == "oikea")
    {
        answer.value = "true";
    }

    setVerdict(answer, answer.value == question.jury_answer);
}

void
matchCheck(const Question& question, Answer& answer)
{
}

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
    std::vector<Question> question(1);

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
    }

    std::vector<std::set<std::string>> wrong(question.size());
    for (auto& i : answers)
    {
        int id = i.question_id;
        if (answer.value != question[id].jury_answer)
        {
            wrong[id].insert(answer.value);
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
        else
        {
        }
        std::cout << std::endl;
    }
    //     for (auto& i : answers)
    //     {
    //         std::cout << answer.value << std::endl;
    //     }
}
