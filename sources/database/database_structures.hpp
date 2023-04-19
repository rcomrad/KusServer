#ifndef DATABASE_STRUCTURES_HPP
#define DATABASE_STRUCTURES_HPP

//--------------------------------------------------------------------------------

#include "database_wrappers.hpp"

//--------------------------------------------------------------------------------

namespace data
{

struct SchoolBase : public BaseDataStruct<4>
{
    int id = 0;
    std::string full_name;
    std::string short_name;
    std::string start_date;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using School = UpperDataStruct<SchoolBase>;

struct UserBase : public BaseDataStruct<7>
{
    int id = 0;
    std::string login;
    std::string password;
    std::string name;
    std::string surname;
    int role_id   = 0;
    int school_id = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using User = UpperDataStruct<UserBase>;

struct RoleBase : public BaseDataStruct<2>
{
    int id = 0;
    std::string name;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Role = UpperDataStruct<RoleBase>;

struct GradeBase : public BaseDataStruct<3>
{
    int id = 0;
    std::string name;
    int head_id = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Grade = UpperDataStruct<GradeBase>;

struct Grade_studentBase : public BaseDataStruct<3>
{
    int id         = 0;
    int grade_id   = 0;
    int student_id = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Grade_student = UpperDataStruct<Grade_studentBase>;

struct GroupBase : public BaseDataStruct<3>
{
    int id = 0;
    std::string name;
    int grade_id = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Group = UpperDataStruct<GroupBase>;

struct Group_studentBase : public BaseDataStruct<3>
{
    int id         = 0;
    int group_id   = 0;
    int student_id = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Group_student = UpperDataStruct<Group_studentBase>;

struct LessonBase : public BaseDataStruct<6>
{
    int id       = 0;
    int theme_id = 0;
    std::string date_val;
    int journal_table_id = 0;
    std::string homework;
    std::string control;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Lesson = UpperDataStruct<LessonBase>;

struct Journal_tableBase : public BaseDataStruct<9>
{
    int id           = 0;
    int teacher_id   = 0;
    int methodist_id = 0;
    char is_group    = -1;
    int group_id     = 0;
    int subject_id   = 0;
    int plan_id      = 0;
    int head_id      = 0;
    std::string schedule;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Journal_table = UpperDataStruct<Journal_tableBase>;

struct SubjectBase : public BaseDataStruct<2>
{
    int id = 0;
    std::string name;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Subject = UpperDataStruct<SubjectBase>;

struct MarkBase : public BaseDataStruct<5>
{
    int id = 0;
    std::string mark_value;
    int student_id       = 0;
    int lesson_id        = 0;
    int journal_table_id = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Mark = UpperDataStruct<MarkBase>;

struct PlanBase : public BaseDataStruct<4>
{
    int id         = 0;
    int subject_id = 0;
    std::string name;
    std::string url;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Plan = UpperDataStruct<PlanBase>;

struct ThemeBase : public BaseDataStruct<4>
{
    int id      = 0;
    int plan_id = 0;
    std::string name;
    int hour_count = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Theme = UpperDataStruct<ThemeBase>;

struct FileBase : public BaseDataStruct<2>
{
    int id  = 0;
    int num = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using File = UpperDataStruct<FileBase>;

struct Safe_fileBase : public BaseDataStruct<2>
{
    int id  = 0;
    int num = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Safe_file = UpperDataStruct<Safe_fileBase>;

struct HolidayBase : public BaseDataStruct<3>
{
    int id        = 0;
    int school_id = 0;
    std::string date_val;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Holiday = UpperDataStruct<HolidayBase>;

struct CompetitionBase : public BaseDataStruct<4>
{
    int id = 0;
    std::string name;
    std::string start_time;
    std::string end_time;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Competition = UpperDataStruct<CompetitionBase>;

struct User_competitionBase : public BaseDataStruct<3>
{
    int id             = 0;
    int user_id        = 0;
    int competition_id = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using User_competition = UpperDataStruct<User_competitionBase>;

struct ProblemBase : public BaseDataStruct<8>
{
    int id = 0;
    std::string name;
    std::string nickname;
    std::string checker_name;
    int test_count    = 0;
    int example_count = 0;
    int time_limit    = 0;
    int memory_limit  = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Problem = UpperDataStruct<ProblemBase>;

struct Competition_problemBase : public BaseDataStruct<4>
{
    int id = 0;
    std::string name;
    int competition_id = 0;
    int problem_id     = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Competition_problem = UpperDataStruct<Competition_problemBase>;

struct SubmissionBase : public BaseDataStruct<7>
{
    int id         = 0;
    int user_id    = 0;
    int problem_id = 0;
    std::string date_val;
    std::string verdict;
    int test = 0;
    std::string source_name;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Submission = UpperDataStruct<SubmissionBase>;

struct QuestionBase : public BaseDataStruct<6>
{
    int id = 0;
    std::string name;
    std::string nickname;
    int type   = 0;
    int weight = 0;
    std::string jury_answer;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Question = UpperDataStruct<QuestionBase>;

struct Competition_questionBase : public BaseDataStruct<4>
{
    int id = 0;
    std::string name;
    int competition_id = 0;
    int question_id    = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Competition_question = UpperDataStruct<Competition_questionBase>;

struct AnswerBase : public BaseDataStruct<7>
{
    int id          = 0;
    int user_id     = 0;
    int question_id = 0;
    std::string time;
    std::string verdict;
    int weight = 0;
    std::string value;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using Answer = UpperDataStruct<AnswerBase>;

struct File_exchangeBase : public BaseDataStruct<6>
{
    int id = 0;
    std::string type;
    std::string direction;
    std::string index;
    std::string name;
    std::string extension;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::vector<std::string> names;
    static std::unordered_map<std::string, uint8_t> nameToNum;

    void reset();
};

using File_exchange = UpperDataStruct<File_exchangeBase>;

} // namespace data

//--------------------------------------------------------------------------------

#endif // !DATABASE_STRUCTURES_HPP
