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
    static std::unordered_map<std::string, uint8_t> columnNames;

    void reset();
};

struct School : public UpperDataStruct<SchoolBase>
{
};

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
    static std::unordered_map<std::string, uint8_t> columnNames;

    void reset();
};

struct User : public UpperDataStruct<UserBase>
{
};

struct RoleBase : public BaseDataStruct<2>
{
    int id = 0;
    std::string name;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::unordered_map<std::string, uint8_t> columnNames;

    void reset();
};

struct Role : public UpperDataStruct<RoleBase>
{
};

struct GradeBase : public BaseDataStruct<3>
{
    int id = 0;
    std::string name;
    int head_id = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::unordered_map<std::string, uint8_t> columnNames;

    void reset();
};

struct Grade : public UpperDataStruct<GradeBase>
{
};

struct Grade_studentBase : public BaseDataStruct<3>
{
    int id         = 0;
    int grade_id   = 0;
    int student_id = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::unordered_map<std::string, uint8_t> columnNames;

    void reset();
};

struct Grade_student : public UpperDataStruct<Grade_studentBase>
{
};

struct GroupBase : public BaseDataStruct<3>
{
    int id = 0;
    std::string name;
    int grade_id = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::unordered_map<std::string, uint8_t> columnNames;

    void reset();
};

struct Group : public UpperDataStruct<GroupBase>
{
};

struct Group_studentBase : public BaseDataStruct<3>
{
    int id         = 0;
    int group_id   = 0;
    int student_id = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::unordered_map<std::string, uint8_t> columnNames;

    void reset();
};

struct Group_student : public UpperDataStruct<Group_studentBase>
{
};

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
    static std::unordered_map<std::string, uint8_t> columnNames;

    void reset();
};

struct Lesson : public UpperDataStruct<LessonBase>
{
};

struct Journal_tableBase : public BaseDataStruct<9>
{
    int id           = 0;
    int teacher_id   = 0;
    int methodist_id = 0;
    bool is_group;
    int group_id   = 0;
    int subject_id = 0;
    int plan_id    = 0;
    int head_id    = 0;
    std::string schedule;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::unordered_map<std::string, uint8_t> columnNames;

    void reset();
};

struct Journal_table : public UpperDataStruct<Journal_tableBase>
{
};

struct SubjectBase : public BaseDataStruct<2>
{
    int id = 0;
    std::string name;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::unordered_map<std::string, uint8_t> columnNames;

    void reset();
};

struct Subject : public UpperDataStruct<SubjectBase>
{
};

struct MarkBase : public BaseDataStruct<5>
{
    int id = 0;
    std::string mark_value;
    int student_id       = 0;
    int lesson_id        = 0;
    int journal_table_id = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::unordered_map<std::string, uint8_t> columnNames;

    void reset();
};

struct Mark : public UpperDataStruct<MarkBase>
{
};

struct PlanBase : public BaseDataStruct<4>
{
    int id         = 0;
    int subject_id = 0;
    std::string name;
    std::string url;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::unordered_map<std::string, uint8_t> columnNames;

    void reset();
};

struct Plan : public UpperDataStruct<PlanBase>
{
};

struct ThemeBase : public BaseDataStruct<4>
{
    int id      = 0;
    int plan_id = 0;
    std::string name;
    int hour_count = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::unordered_map<std::string, uint8_t> columnNames;

    void reset();
};

struct Theme : public UpperDataStruct<ThemeBase>
{
};

struct FileBase : public BaseDataStruct<2>
{
    int id  = 0;
    int num = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::unordered_map<std::string, uint8_t> columnNames;

    void reset();
};

struct File : public UpperDataStruct<FileBase>
{
};

struct HolidayBase : public BaseDataStruct<3>
{
    int id        = 0;
    int school_id = 0;
    std::string date_val;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::unordered_map<std::string, uint8_t> columnNames;

    void reset();
};

struct Holiday : public UpperDataStruct<HolidayBase>
{
};

struct ProblemBase : public BaseDataStruct<2>
{
    int id    = 0;
    int index = 0;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::unordered_map<std::string, uint8_t> columnNames;

    void reset();
};

struct Problem : public UpperDataStruct<ProblemBase>
{
};

struct SubmissionBase : public BaseDataStruct<5>
{
    int id         = 0;
    int user_id    = 0;
    int problem_id = 0;
    std::string date_val;
    std::string verdict;

    static std::string tableName;
    static std::vector<data::Type> types;
    static std::unordered_map<std::string, uint8_t> columnNames;

    void reset();
};

struct Submission : public UpperDataStruct<SubmissionBase>
{
};

} // namespace data

//--------------------------------------------------------------------------------

#endif // !DATABASE_STRUCTURES_HPP
