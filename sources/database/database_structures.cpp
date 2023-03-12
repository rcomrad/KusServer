#include "database_structures.hpp"

#include <cstring>

#include "core/core.hpp"

std::string data::SchoolBase::tableName         = "school";
std::vector<data::Type> data::SchoolBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING,
    data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::SchoolBase::columnNames = {
    {"id",         0},
    {"full_name",  1},
    {"short_name", 2},
    {"start_date", 3}
};

void
data::SchoolBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&full_name);
    ptrs[2] = (void*)(&short_name);
    ptrs[3] = (void*)(&start_date);
}

std::string data::UserBase::tableName         = "user";
std::vector<data::Type> data::UserBase::types = {
    data::Type::INT,    data::Type::STRING, data::Type::STRING,
    data::Type::STRING, data::Type::STRING, data::Type::INT,
    data::Type::INT};
std::unordered_map<std::string, uint8_t> data::UserBase::columnNames = {
    {"id",        0},
    {"login",     1},
    {"password",  2},
    {"name",      3},
    {"surname",   4},
    {"role_id",   5},
    {"school_id", 6}
};

void
data::UserBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&login);
    ptrs[2] = (void*)(&password);
    ptrs[3] = (void*)(&name);
    ptrs[4] = (void*)(&surname);
    ptrs[5] = (void*)(&role_id);
    ptrs[6] = (void*)(&school_id);
}

std::string data::RoleBase::tableName         = "role";
std::vector<data::Type> data::RoleBase::types = {data::Type::INT,
                                                 data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::RoleBase::columnNames = {
    {"id",   0},
    {"name", 1}
};

void
data::RoleBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&name);
}

std::string data::GradeBase::tableName         = "grade";
std::vector<data::Type> data::GradeBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::INT};
std::unordered_map<std::string, uint8_t> data::GradeBase::columnNames = {
    {"id",      0},
    {"name",    1},
    {"head_id", 2}
};

void
data::GradeBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&name);
    ptrs[2] = (void*)(&head_id);
}

std::string data::Grade_studentBase::tableName         = "grade_student";
std::vector<data::Type> data::Grade_studentBase::types = {
    data::Type::INT, data::Type::INT, data::Type::INT};
std::unordered_map<std::string, uint8_t> data::Grade_studentBase::columnNames =
    {
        {"id",         0},
        {"grade_id",   1},
        {"student_id", 2}
};

void
data::Grade_studentBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&grade_id);
    ptrs[2] = (void*)(&student_id);
}

std::string data::GroupBase::tableName         = "group";
std::vector<data::Type> data::GroupBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::INT};
std::unordered_map<std::string, uint8_t> data::GroupBase::columnNames = {
    {"id",       0},
    {"name",     1},
    {"grade_id", 2}
};

void
data::GroupBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&name);
    ptrs[2] = (void*)(&grade_id);
}

std::string data::Group_studentBase::tableName         = "group_student";
std::vector<data::Type> data::Group_studentBase::types = {
    data::Type::INT, data::Type::INT, data::Type::INT};
std::unordered_map<std::string, uint8_t> data::Group_studentBase::columnNames =
    {
        {"id",         0},
        {"group_id",   1},
        {"student_id", 2}
};

void
data::Group_studentBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&group_id);
    ptrs[2] = (void*)(&student_id);
}

std::string data::LessonBase::tableName         = "lesson";
std::vector<data::Type> data::LessonBase::types = {
    data::Type::INT, data::Type::INT,    data::Type::STRING,
    data::Type::INT, data::Type::STRING, data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::LessonBase::columnNames = {
    {"id",               0},
    {"theme_id",         1},
    {"date_val",         2},
    {"journal_table_id", 3},
    {"homework",         4},
    {"control",          5}
};

void
data::LessonBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&theme_id);
    ptrs[2] = (void*)(&date_val);
    ptrs[3] = (void*)(&journal_table_id);
    ptrs[4] = (void*)(&homework);
    ptrs[5] = (void*)(&control);
}

std::string data::Journal_tableBase::tableName         = "journal_table";
std::vector<data::Type> data::Journal_tableBase::types = {
    data::Type::INT,  data::Type::INT, data::Type::INT,
    data::Type::BOOL, data::Type::INT, data::Type::INT,
    data::Type::INT,  data::Type::INT, data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::Journal_tableBase::columnNames =
    {
        {"id",           0},
        {"teacher_id",   1},
        {"methodist_id", 2},
        {"is_group",     3},
        {"group_id",     4},
        {"subject_id",   5},
        {"plan_id",      6},
        {"head_id",      7},
        {"schedule",     8}
};

void
data::Journal_tableBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&teacher_id);
    ptrs[2] = (void*)(&methodist_id);
    ptrs[3] = (void*)(&is_group);
    ptrs[4] = (void*)(&group_id);
    ptrs[5] = (void*)(&subject_id);
    ptrs[6] = (void*)(&plan_id);
    ptrs[7] = (void*)(&head_id);
    ptrs[8] = (void*)(&schedule);
}

std::string data::SubjectBase::tableName         = "subject";
std::vector<data::Type> data::SubjectBase::types = {data::Type::INT,
                                                    data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::SubjectBase::columnNames = {
    {"id",   0},
    {"name", 1}
};

void
data::SubjectBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&name);
}

std::string data::MarkBase::tableName         = "mark";
std::vector<data::Type> data::MarkBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::INT, data::Type::INT,
    data::Type::INT};
std::unordered_map<std::string, uint8_t> data::MarkBase::columnNames = {
    {"id",               0},
    {"mark_value",       1},
    {"student_id",       2},
    {"lesson_id",        3},
    {"journal_table_id", 4}
};

void
data::MarkBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&mark_value);
    ptrs[2] = (void*)(&student_id);
    ptrs[3] = (void*)(&lesson_id);
    ptrs[4] = (void*)(&journal_table_id);
}

std::string data::PlanBase::tableName         = "plan";
std::vector<data::Type> data::PlanBase::types = {
    data::Type::INT, data::Type::INT, data::Type::STRING, data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::PlanBase::columnNames = {
    {"id",         0},
    {"subject_id", 1},
    {"name",       2},
    {"url",        3}
};

void
data::PlanBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&subject_id);
    ptrs[2] = (void*)(&name);
    ptrs[3] = (void*)(&url);
}

std::string data::ThemeBase::tableName         = "theme";
std::vector<data::Type> data::ThemeBase::types = {
    data::Type::INT, data::Type::INT, data::Type::STRING, data::Type::INT};
std::unordered_map<std::string, uint8_t> data::ThemeBase::columnNames = {
    {"id",         0},
    {"plan_id",    1},
    {"name",       2},
    {"hour_count", 3}
};

void
data::ThemeBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&plan_id);
    ptrs[2] = (void*)(&name);
    ptrs[3] = (void*)(&hour_count);
}

std::string data::FileBase::tableName         = "file";
std::vector<data::Type> data::FileBase::types = {data::Type::INT,
                                                 data::Type::INT};
std::unordered_map<std::string, uint8_t> data::FileBase::columnNames = {
    {"id",  0},
    {"num", 1}
};

void
data::FileBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&num);
}

std::string data::HolidayBase::tableName         = "holiday";
std::vector<data::Type> data::HolidayBase::types = {
    data::Type::INT, data::Type::INT, data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::HolidayBase::columnNames = {
    {"id",        0},
    {"school_id", 1},
    {"date_val",  2}
};

void
data::HolidayBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&school_id);
    ptrs[2] = (void*)(&date_val);
}

std::string data::ProblemBase::tableName         = "problem";
std::vector<data::Type> data::ProblemBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::ProblemBase::columnNames = {
    {"id",       0},
    {"name",     1},
    {"nickname", 2}
};

void
data::ProblemBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&name);
    ptrs[2] = (void*)(&nickname);
}

std::string data::SubmissionBase::tableName         = "submission";
std::vector<data::Type> data::SubmissionBase::types = {
    data::Type::INT,    data::Type::INT, data::Type::INT,   data::Type::STRING,
    data::Type::STRING, data::Type::INT, data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::SubmissionBase::columnNames = {
    {"id",         0},
    {"user_id",    1},
    {"problem_id", 2},
    {"date_val",   3},
    {"verdict",    4},
    {"test",       5},
    {"file_path",  6}
};

void
data::SubmissionBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&user_id);
    ptrs[2] = (void*)(&problem_id);
    ptrs[3] = (void*)(&date_val);
    ptrs[4] = (void*)(&verdict);
    ptrs[5] = (void*)(&test);
    ptrs[6] = (void*)(&file_path);
}

std::string data::User_uploadBase::tableName         = "user_upload";
std::vector<data::Type> data::User_uploadBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING,
    data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::User_uploadBase::columnNames = {
    {"id",        0},
    {"index",     1},
    {"name",      2},
    {"extension", 3}
};

void
data::User_uploadBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&index);
    ptrs[2] = (void*)(&name);
    ptrs[3] = (void*)(&extension);
}

std::string data::Plan_uploadBase::tableName         = "plan_upload";
std::vector<data::Type> data::Plan_uploadBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING,
    data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::Plan_uploadBase::columnNames = {
    {"id",        0},
    {"index",     1},
    {"name",      2},
    {"extension", 3}
};

void
data::Plan_uploadBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&index);
    ptrs[2] = (void*)(&name);
    ptrs[3] = (void*)(&extension);
}

std::string data::Journal_uploadBase::tableName         = "journal_upload";
std::vector<data::Type> data::Journal_uploadBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING,
    data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::Journal_uploadBase::columnNames =
    {
        {"id",        0},
        {"index",     1},
        {"name",      2},
        {"extension", 3}
};

void
data::Journal_uploadBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&index);
    ptrs[2] = (void*)(&name);
    ptrs[3] = (void*)(&extension);
}

std::string data::Journal_downloadBase::tableName         = "journal_download";
std::vector<data::Type> data::Journal_downloadBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING,
    data::Type::STRING};
std::unordered_map<std::string, uint8_t>
    data::Journal_downloadBase::columnNames = {
        {"id",        0},
        {"index",     1},
        {"name",      2},
        {"extension", 3}
};

void
data::Journal_downloadBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&index);
    ptrs[2] = (void*)(&name);
    ptrs[3] = (void*)(&extension);
}

std::string data::QuestionBase::tableName         = "question";
std::vector<data::Type> data::QuestionBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING,
    data::Type::INT, data::Type::INT,    data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::QuestionBase::columnNames = {
    {"id",          0},
    {"title",       1},
    {"legend",      2},
    {"type",        3},
    {"contest",     4},
    {"jury_answer", 5}
};

void
data::QuestionBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&title);
    ptrs[2] = (void*)(&legend);
    ptrs[3] = (void*)(&type);
    ptrs[4] = (void*)(&contest);
    ptrs[5] = (void*)(&jury_answer);
}

std::string data::Question_typeBase::tableName         = "question_type";
std::vector<data::Type> data::Question_typeBase::types = {data::Type::INT,
                                                          data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::Question_typeBase::columnNames =
    {
        {"id",   0},
        {"name", 1}
};

void
data::Question_typeBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&name);
}

std::string data::User_answerBase::tableName         = "user_answer";
std::vector<data::Type> data::User_answerBase::types = {
    data::Type::INT,    data::Type::INT,    data::Type::INT,
    data::Type::STRING, data::Type::STRING, data::Type::STRING,
    data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::User_answerBase::columnNames = {
    {"id",          0},
    {"user_id",     1},
    {"question_id", 2},
    {"user_answer", 3},
    {"time",        4},
    {"true_time",   5},
    {"is_correct",  6}
};

void
data::User_answerBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&user_id);
    ptrs[2] = (void*)(&question_id);
    ptrs[3] = (void*)(&user_answer);
    ptrs[4] = (void*)(&time);
    ptrs[5] = (void*)(&true_time);
    ptrs[6] = (void*)(&is_correct);
}
