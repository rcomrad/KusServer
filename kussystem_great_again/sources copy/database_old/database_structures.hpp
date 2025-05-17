#ifndef DATABASE_STRUCTURES_HPP
#define DATABASE_STRUCTURES_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "database_wrappers.hpp"

namespace data
{
struct AnswerBase : public BaseDataStruct<7>
{
    int id         = 0;
    int userID     = 0;
    int questionID = 0;
    str::String time;
    str::String verdict;
    float weight;
    str::String value;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using Answer = UpperDataStruct<AnswerBase>;

struct CompetitionBase : public BaseDataStruct<4>
{
    int id = 0;
    str::String name;
    str::String startTime;
    str::String endTime;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using Competition = UpperDataStruct<CompetitionBase>;

struct CompetitionProblemBase : public BaseDataStruct<4>
{
    int id            = 0;
    int competitionID = 0;
    int problemID     = 0;
    str::String name;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using CompetitionProblem = UpperDataStruct<CompetitionProblemBase>;

struct CompetitionQuestionBase : public BaseDataStruct<4>
{
    int id            = 0;
    int competitionID = 0;
    int questionID    = 0;
    str::String name;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using CompetitionQuestion = UpperDataStruct<CompetitionQuestionBase>;

struct CompetitionUserBase : public BaseDataStruct<3>
{
    int id            = 0;
    int competitionID = 0;
    int userID        = 0;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using CompetitionUser = UpperDataStruct<CompetitionUserBase>;

struct DummyBase : public BaseDataStruct<1>
{
    int id = 0;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using Dummy = UpperDataStruct<DummyBase>;

struct FieldBase : public BaseDataStruct<5>
{
    int id = 0;
    str::String type;
    str::String info;
    str::String name;
    str::String label;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using Field = UpperDataStruct<FieldBase>;

struct FieldFormBase : public BaseDataStruct<3>
{
    int id      = 0;
    int fieldID = 0;
    int formID  = 0;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using FieldForm = UpperDataStruct<FieldFormBase>;

struct FileBase : public BaseDataStruct<2>
{
    int id  = 0;
    int num = 0;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using File = UpperDataStruct<FileBase>;

struct FormBase : public BaseDataStruct<6>
{
    int id = 0;
    str::String module;
    str::String userName;
    str::String techName;
    str::String roleStr;
    int roleID = 0;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using Form = UpperDataStruct<FormBase>;

struct GradeBase : public BaseDataStruct<4>
{
    int id = 0;
    str::String name;
    int headID   = 0;
    char isGroup = 0;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using Grade = UpperDataStruct<GradeBase>;

struct GradeStudentBase : public BaseDataStruct<3>
{
    int id        = 0;
    int gradeID   = 0;
    int studentID = 0;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using GradeStudent = UpperDataStruct<GradeStudentBase>;

struct HolidayBase : public BaseDataStruct<3>
{
    int id       = 0;
    int schoolID = 0;
    str::String dateVal;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using Holiday = UpperDataStruct<HolidayBase>;

struct JournalTableBase : public BaseDataStruct<8>
{
    int id          = 0;
    int teacherID   = 0;
    int methodistID = 0;
    int gradeID     = 0;
    int subjectID   = 0;
    int planID      = 0;
    int headID      = 0;
    str::String schedule;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using JournalTable = UpperDataStruct<JournalTableBase>;

struct LessonBase : public BaseDataStruct<6>
{
    int id      = 0;
    int themeID = 0;
    str::String dateVal;
    int journalTableID = 0;
    str::String homework;
    str::String control;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using Lesson = UpperDataStruct<LessonBase>;

struct MarkBase : public BaseDataStruct<5>
{
    int id = 0;
    str::String markValue;
    int studentID      = 0;
    int lessonID       = 0;
    int journalTableID = 0;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using Mark = UpperDataStruct<MarkBase>;

struct PlanBase : public BaseDataStruct<4>
{
    int id        = 0;
    int subjectID = 0;
    str::String name;
    str::String url;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using Plan = UpperDataStruct<PlanBase>;

struct ProblemBase : public BaseDataStruct<8>
{
    int id = 0;
    str::String name;
    str::String nickname;
    str::String checkerName;
    int testCount    = 0;
    int exampleCount = 0;
    int timeLimit    = 0;
    int memoryLimit  = 0;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using Problem = UpperDataStruct<ProblemBase>;

struct QuestionBase : public BaseDataStruct<6>
{
    int id = 0;
    str::String name;
    str::String nickname;
    str::String type;
    float weight;
    str::String juryAnswer;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using Question = UpperDataStruct<QuestionBase>;

struct RoleBase : public BaseDataStruct<2>
{
    int id = 0;
    str::String name;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using Role = UpperDataStruct<RoleBase>;

struct SafeFileBase : public BaseDataStruct<2>
{
    int id  = 0;
    int num = 0;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using SafeFile = UpperDataStruct<SafeFileBase>;

struct SchoolBase : public BaseDataStruct<4>
{
    int id = 0;
    str::String fullName;
    str::String shortName;
    str::String startDate;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using School = UpperDataStruct<SchoolBase>;

struct SubjectBase : public BaseDataStruct<2>
{
    int id = 0;
    str::String name;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using Subject = UpperDataStruct<SubjectBase>;

struct SubmissionBase : public BaseDataStruct<7>
{
    int id        = 0;
    int userID    = 0;
    int problemID = 0;
    str::String dateVal;
    str::String verdict;
    int test = 0;
    str::String sourceName;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using Submission = UpperDataStruct<SubmissionBase>;

struct ThemeBase : public BaseDataStruct<4>
{
    int id     = 0;
    int planID = 0;
    str::String name;
    int hourCount = 0;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using Theme = UpperDataStruct<ThemeBase>;

struct TokenBase : public BaseDataStruct<6>
{
    int id = 0;
    str::String startTime;
    str::String value;
    int userID   = 0;
    int userRole = 0;
    str::String userIp;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using Token = UpperDataStruct<TokenBase>;

struct UserBase : public BaseDataStruct<11>
{
    int id = 0;
    str::String login;
    str::String password;
    str::String email;
    str::String lastLogin;
    str::String name;
    str::String surname;
    int schoolID = 0;
    str::String key;
    int status = 0;
    int roleID = 0;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using User = UpperDataStruct<UserBase>;

struct UserRegistrationBase : public BaseDataStruct<3>
{
    int id     = 0;
    int userID = 0;
    str::String link;

    static str::String tableName;
    static std::vector<data::Type> types;
    static std::vector<str::String> columnNames;
    static std::unordered_map<str::String, uint8_t> nameToNum;

    void reset();
};

using UserRegistration = UpperDataStruct<UserRegistrationBase>;

}; // namespace data

#endif // !DATABASE_STRUCTURES_HPP
