#include "evaluate.hpp"

#include <boost/locale.hpp>

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

#include "utility/string/parser.hpp"
#include "utility/string/slicer.hpp"

std::string
translitor(const std::string& a_str)
{
    std::map<std::string, std::string> mapping = {
        {"А", "A"},
        {"Б", "B"},
        {"В", "B"},
        {"Г", "G"},
        {"Д", "D"},
        {"Е", "E"},
        {"Ё", "e"},
        {"Ж", "J"},
        {"З", "Z"},
        {"И", "I"},
        {"Й", "Y"},
        {"К", "K"},
        {"Л", "L"},
        {"М", "M"},
        {"Н", "N"},
        {"О", "O"},
        {"П", "P"},
        {"Р", "R"},
        {"С", "S"},
        {"Т", "T"},
        {"У", "U"},
        {"Ф", "F"},
        {"Х", "H"},
        {"Ц", "C"},
        {"Ч", "h"},
        {"Ш", "s"},
        {"Щ", "c"},
        {"Ъ", "`"},
        {"Ы", "y"},
        {"Ь", "'"},
        {"Э", "u"},
        {"Ю", "u"},
        {"Я", "a"},
        {"а", "A"},
        {"б", "B"},
        {"в", "B"},
        {"г", "G"},
        {"д", "D"},
        {"е", "E"},
        {"ё", "e"},
        {"ж", "J"},
        {"з", "Z"},
        {"и", "I"},
        {"й", "Y"},
        {"к", "K"},
        {"л", "L"},
        {"м", "M"},
        {"н", "N"},
        {"о", "O"},
        {"п", "P"},
        {"р", "R"},
        {"с", "S"},
        {"т", "T"},
        {"у", "U"},
        {"ф", "F"},
        {"х", "H"},
        {"ц", "C"},
        {"ч", "h"},
        {"ш", "s"},
        {"щ", "c"},
        {"ъ", "`"},
        {"ы", "y"},
        {"б", "'"},
        {"э", "u"},
        {"ю", "u"},
        {"я", "a"},
    };

    for (char c = 'a'; c <= 'z'; ++c)
    {
        std::string f{c};
        std::string e{(char)(c - ('a' - 'A'))};
        mapping[f] = e;
    }
    std::set<char> simpl{'.', ',', ')', '(', ' ', '"', '\''};
    std::string result;
    std::string temp;
    for (auto i : a_str)
    {
        if (simpl.count(i))
        {
            result += i;
            continue;
        }
        temp += i;
        auto it = mapping.find(temp);
        if (it != mapping.end())
        {
            result += it->second;
            temp.clear();
        }
    }
    result += temp;
    return result;
}

void
inplace_translitor(std::string& a_str)
{
    // std::cout << a_str << std::endl;
    // a_str = translitor(a_str);
}

std::string
customTransliterate(const std::string& input,
                    const std::map<char, std::string>& mapping)
{
    std::string output;
    for (char ch : input)
    {
        auto it = mapping.find(ch);
        if (it != mapping.end())
        {
            output += it->second; // Append mapped value
        }
        else
        {
            output += ch; // Append original character if no mapping found
        }
    }
    return output;
}

int
foo()
{
    // Define your custom mapping

    // std::string input  = "Привет"; // Input string in Cyrillic
    // std::string output = customTransliterate(input, mapping);

    // std::cout << "Original: " << input << std::endl;
    // std::cout << "Transliterated: " << output << std::endl;

    return 0;
}

// std::u16string
// utf8_to_utf16(const std::string& utf8_str)
// {
//     // Set up the locale for UTF-8
//     boost::locale::generator gen;
//     std::locale loc = gen("en_US.UTF-8");

//     // Convert the UTF-8 string to UTF-16
//     std::wstring_convert<std::codecvt_utf8_utf16<char16_t>> converter;
//     std::u16string utf16_str = converter.from_bytes(utf8_str);

//     return utf16_str;
// }
// #include <codecvt>
// std::wstring
// utf8_to_wstring_normalized(const std::string& utf8_str)
// {
//     // Normalize the UTF-8 string using NFC (Normalization Form C)
//     std::string normalized_str =
//         boost::locale::normalize(utf8_str, boost::locale::norm_nfc);

//     // Convert the normalized UTF-8 string to std::wstring (UTF-16)
//     std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
//     std::wstring wstr = converter.from_bytes(normalized_str);

//     return wstr;
// }

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
    std::unordered_set<std::string> good;
    std::unordered_set<std::string> bad;

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
        if (a_data.size() != 7) exit(0);
    }
};

struct User
{
    int id;
    std::string login;
    std::string password;
    std::string email;
    std::string last_login;
    std::string name;
    std::string surname;
    int school_id;
    std::string key;
    int status;
    int role_id;

    int cl11 = false;

    std::vector<int> tasks;

    User()
    {
    }
    User(const std::vector<std::string_view>& a_data)
    {
        id         = to_int(a_data[0]);
        login      = (a_data[1]);
        password   = (a_data[2]);
        email      = (a_data[3]);
        last_login = (a_data[4]);
        name       = (a_data[5]);
        surname    = (a_data[6]);
        school_id  = to_int(a_data[7]);
        key        = (a_data[8]);
        status     = to_int(a_data[9]);
        role_id    = to_int(a_data[10]);
        // std::cout <<" >>>>>>" << a_data[1] << "\n";
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
setVerdict(Answer& answer, bool verdict)
{
    if (verdict)
    {
        answer.verdict = 1;
    }
    else
    {
        answer.verdict = 0;
    }
}

void
boolCheck(const Question& question, Answer& answer)
{
    answer.value = translitor(answer.value);

    if (answer.value == "нет" || answer.value == "неверно" ||
        answer.value == "NEBERNO" || answer.value == "НЕВЕРНО" ||
        answer.value == "неверно " || answer.value == "Неверно" ||
        answer.value == "НЕТ" || answer.value == "NET" ||
        answer.value == "No" || answer.value == "NO" ||
        answer.value == " нет" || answer.value == "нет " ||
        answer.value == "НЕТ " || answer.value == "НКЕТ" ||
        answer.value == "Нет " || answer.value == "НЕT" ||
        answer.value == " НЕТ" || answer.value == "HET" ||
        answer.value == "NKET" || answer.value == "Нет" ||
        answer.value == "No" || answer.value == "no" ||
        answer.value == "väärin" || answer.value == "не" ||
        answer.value == "väärin " || answer.value == "VIRHEELLINEN" ||
        answer.value == "Väärin" || answer.value == "virheellinen")
    {
        answer.value = "FALSE";
    }
    else if (answer.value == "да" || answer.value == "верно" ||
             answer.value == "BERNO" || answer.value == "ВЕРНО" ||
             answer.value == "OIKEA" || answer.value == "OIKEIN" ||
             answer.value == "ДАТ" || answer.value == "Yes" ||
             answer.value == "Д" || answer.value == "А" ||
             answer.value == "а" || answer.value == "ДА" ||
             answer.value == "Да" || answer.value == "да " ||
             answer.value == "ВЕРНО " || answer.value == "yes" ||
             answer.value == "Yes" || answer.value == "Да " ||
             answer.value == "ДА " || answer.value == "DAT" ||
             answer.value == " ДА" || answer.value == " DA" ||
             answer.value == "DA" || answer.value == "D" ||
             answer.value == "A" || answer.value == "YES" ||
             answer.value == "Верно" || answer.value == "oikein" ||
             answer.value == "oikea")
    {
        answer.value = "TRUE";
    }
    else
    {
        std::cout << "=============" << answer.value << std::endl;
    }

    answer.verdict = 0;
    if (answer.value == translitor(question.jury_answer))
    {
        answer.verdict = 1;
    }

    // setVerdict(answer, answer.value == question.jury_answer);
}

void
singlCheck(const Question& question, Answer& answer)
{
    answer.verdict = 0;
    if (answer.value == question.jury_answer)
    {
        answer.verdict = 1;
    }

    // setVerdict(answer, answer.value == question.jury_answer);
}

void
countCheck(const Question& question, Answer& answer)
{
    int res = 0;
    if (question.jury_answer.size() == answer.value.size())
    {
        for (int i = 0; i < answer.value.size(); ++i)
        {
            if (answer.value[i] == question.jury_answer[i])
            {
                ++res;
            }
        }
    }
    answer.verdict = res;
}

void
wordCheck(const Question& question, Answer& answer)
{
    std::string ans_str{question.jury_answer};
    std::string part_str{answer.value};
    // answer.value.clear();

    auto ans_v = util::Slicer::process(ans_str, ", \t.;");
    auto part  = util::Slicer::process(part_str, ", \t.;");

    int res = 0;
    std::unordered_set<std::string> ans;
    for (auto& i : ans_v) ans.insert(translitor(std::string(i)));
    for (auto& i : part)
    {
        if (ans.count(translitor(std::string(i))))
        {
            res++;
            answer.good.insert(std::string(i));
        }
        else
        {
            std::cout << "???????????? " << i << std::endl;
            answer.bad.insert(std::string(i));
        }
    }
    answer.verdict = res;
}

void
dublCheck(const Question& question, Answer& answer)
{
    std::string temp = question.jury_answer;
    auto f           = util::Slicer::process(temp, ",");
    auto s           = util::Slicer::process(answer.value, ",");

    answer.verdict = 0;
    if (f[0] == s[0] || f[0] == s[1]) answer.verdict++;
    if (f[1] == s[1] || f[1] == s[0]) answer.verdict++;
}

void
matchCheck(const Question& question, Answer& answer)
{
}
#include "utility/string/slicer.hpp"
void
olymp::Evaluate::processResults(core::CommandExtend& a_command) noexcept
{
    int border = 45;

    CMD_ASSERT(argCount(1).noVars());
    auto& file_name = a_command.arguments[0];

    std::ifstream file(file_name.data());
    std::string data;
    std::getline(file, data, '\0');
    auto words = util::Parser::getWords(data, ";\t\"\'");
    std::vector<User> users(2000);
    std::vector<Answer> answers(1);
    std::vector<Question> question(1);
    int num = 0;
    for (auto& i : words)
    {
        //   if (i.size())  std::cout << i[0] << std::endl;
        // continue;

        if (i.empty()) continue;

        // for (auto& j : i) std::cout << j << " ";
        // if (i.size() > 1) std::cout << i[0] << " " << i[1] << std::endl;
        // if (i[0] == "749")
        // {
        //     int yy = 0;
        //     yy++;
        // }
        // continue;

        if (i[0] == "user")
        {
            num = 3;
            continue;
        }
        else if (i[0] == "answer")
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

        std::string* ptr = nullptr;
        bool flag        = false;
        switch (num)
        {
            case 1:
                ptr = &answers.emplace_back(i).value;
                // flag = question[answers.back().question_id].type != "stat";
                flag = question[answers.back().question_id].type == "singl" ||
                       question.back().type == "count";
                if (answers.back().id == 14398)
                {
                    int yy = 0;
                    yy++;
                }
                if (answers.back().question_id > border)
                {
                    answers.pop_back();
                    flag = false;
                }
                break;
            case 2:
                ptr = &question.emplace_back(i).jury_answer;
                // flag = question.back().type != "stat";
                flag = question.back().type == "singl" ||
                       question.back().type == "count";
                break;
            case 3:
                users[std::stoi(std::string(i[0]))] = User(i);
                break;
        }
        // if (ptr && flag)
        // {
        //     inplace_translitor(*ptr);
        //     auto word = util::Slicer::process(*ptr, "", " )");
        //     if (word.size() > 1)
        //     {
        //         std::cout << *ptr << "\n";
        //         // std::flush(stdout);
        //         // exit(0);
        //     }
        //     if (word.size())
        //     {
        //         *ptr = std::string(word[0]);
        //     }

        //     // if (*ptr == "B1991") *ptr = "B";
        // }
    }

    // for (auto& i : users)
    // {
    //     std::cout << i.login << std::endl;
    // }
    // return ;
    std::cout << "=========================================" << std::endl;
    std::vector<std::unordered_set<std::string>> wrong(question.size());
    std::vector<std::unordered_set<std::string>> good(question.size());

    std::vector<std::vector<int>> table(users.size(), std::vector<int>());

    answers[0].id          = 0;
    answers[0].question_id = 0;
    answers[0].time        = "2024-10-10 17:00:00";
    answers[0].verdict     = 0;
    question[0].id         = 0;
    question[0].type       = "NUN";
    for (auto& i : answers)
    {
        // std::cout << i.id << " " << i.value << std::endl;

        int id  = i.question_id;
        auto& q = question[id];
        auto& u = users[i.user_id];
        if (i.id == 1600)
        {
            int yy = 0;
            yy++;
        }

        // if (u.login == "GIDLA-911-02")
        // {
        //     int yy = 0;
        //     yy++;
        // }

        // if (u.id == 97 || u.id == 94 || u.id == 333)
        // {
        //     continue;
        // }

        auto time = util::Slicer::process(i.time, " -:");
        if (i.time.size() &&
            std::stoi(std::string(time[3]) + std::string(time[4])) >= 1330)
        {
            std::cout << "timr!!!! :" << time[3] << ":" << time[4] << "\n";
            continue;
        }
        else if (i.time.size())
        {
            std::cout << "timr~~~ :" << time[3] << ":" << time[4] << "\n";
        }

        // if (u.id != 132)
        // if (u.id != 308)
        // {
        //     continue;
        // }

        // std::cout << ">>>" << "log: " << "-" << u.login << "-\n";

        if (q.type == "singl")
        {
            singlCheck(q, i);
        }
        if (q.type == "bool")
        {
            boolCheck(q, i);
        }
        else if (q.type == "count")
        {
            countCheck(q, i);
        }
        else if (q.type == "dubl")
        {
            dublCheck(q, i);
        }
        else if (q.type == "word")
        {
            wordCheck(q, i);
            wrong[id].insert(i.bad.begin(), i.bad.end());
            good[id].insert(i.good.begin(), i.good.end());
        }

        if (q.type != "word")
        {
            if (i.verdict == 0)
            {
                wrong[id].insert(i.value);
                if (id == 1)
                {
                    int yy = 0;
                    yy++;
                }
            }
            else
            {
                good[id].insert(i.value);
            }
        }

        if (u.tasks.size() <= id) u.tasks.resize(id + 1, -1);
        if (u.tasks[id] != -1)
        {
            exit(0);
        }
        u.tasks[id] = i.verdict;

        // int id = i.question_id;
        // if (i.value != question[id].jury_answer)
        // {
        //     // wrong[id].insert(utf8_to_wstring_normalized(i.value));
        //     wrong[id].insert(i.value);
        // }
        // else
        // {
        // }
    }

    int cnt = 0;
    for (int num = 0; num < border; ++num)
    {
        auto& i = wrong[num];
        std::cout << cnt++ << " ";
        for (auto& j : i)
        {
            std::cout << "[" << j << "]" << " ";
        }
        std::cout << " | ";
        for (auto& j : good[num])
        {
            std::cout << "->" << j << "<-" << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "===================================\n";

    for (auto& u : users)
    {
        if (u.tasks.size())
        {
            if (u.cl11 == 11)
            {
                std::cout << "9 ";
                u.tasks.erase(u.tasks.begin(), u.tasks.begin() + 11);
            }
            else
            {
                std::cout << "7 ";
                u.tasks.erase(u.tasks.begin());
            }

            std::cout << u.login << " " << u.password << " ";
            int s = 0;
            for (auto& i : u.tasks)
            {
                if (i == -1) std::cout << "# ";
                else
                {
                    std::cout << i << " ";
                    s += i;
                }
            }

            std::cout << s << "\n";
        }
    }

    std::cout << "FIN" << std::endl;
    //     for (auto& i : answers)
    //     {
    //         std::cout << answer.value << std::endl;
    //     }
}
