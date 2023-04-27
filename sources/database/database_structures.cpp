#include "database_structures.hpp"

#include <cstring>

std::string data::DummyBase::tableName          = "dummy";
std::vector<data::Type> data::DummyBase::types  = {data::Type::INT};
std::vector<std::string> data::DummyBase::names = {"id"};
std::unordered_map<std::string, uint8_t> data::DummyBase::nameToNum = {
    {"id", 0}
};

void
data::DummyBase::reset()
{
    ptrs[0] = (void*)(&id);
}

std::string data::SchoolBase::tableName         = "school";
std::vector<data::Type> data::SchoolBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING,
    data::Type::STRING};
std::vector<std::string> data::SchoolBase::names = {"id", "full_name",
                                                    "short_name", "start_date"};
std::unordered_map<std::string, uint8_t> data::SchoolBase::nameToNum = {
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
std::vector<std::string> data::UserBase::names = {
    "id", "login", "password", "name", "surname", "school_id", "role_id"};
std::unordered_map<std::string, uint8_t> data::UserBase::nameToNum = {
    {"id",        0},
    {"login",     1},
    {"password",  2},
    {"name",      3},
    {"surname",   4},
    {"school_id", 5},
    {"role_id",   6}
};

void
data::UserBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&login);
    ptrs[2] = (void*)(&password);
    ptrs[3] = (void*)(&name);
    ptrs[4] = (void*)(&surname);
    ptrs[5] = (void*)(&school_id);
    ptrs[6] = (void*)(&role_id);
}

std::string data::RoleBase::tableName          = "role";
std::vector<data::Type> data::RoleBase::types  = {data::Type::INT,
                                                  data::Type::STRING};
std::vector<std::string> data::RoleBase::names = {"id", "name"};
std::unordered_map<std::string, uint8_t> data::RoleBase::nameToNum = {
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
std::vector<std::string> data::GradeBase::names = {"id", "name", "head_id"};
std::unordered_map<std::string, uint8_t> data::GradeBase::nameToNum = {
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
std::vector<std::string> data::Grade_studentBase::names = {"id", "grade_id",
                                                           "student_id"};
std::unordered_map<std::string, uint8_t> data::Grade_studentBase::nameToNum = {
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
std::vector<std::string> data::GroupBase::names = {"id", "name", "grade_id"};
std::unordered_map<std::string, uint8_t> data::GroupBase::nameToNum = {
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
std::vector<std::string> data::Group_studentBase::names = {"id", "group_id",
                                                           "student_id"};
std::unordered_map<std::string, uint8_t> data::Group_studentBase::nameToNum = {
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
std::vector<std::string> data::LessonBase::names = {
    "id", "theme_id", "date_val", "journal_table_id", "homework", "control"};
std::unordered_map<std::string, uint8_t> data::LessonBase::nameToNum = {
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
std::vector<std::string> data::Journal_tableBase::names = {
    "id",         "teacher_id", "methodist_id", "is_group", "group_id",
    "subject_id", "plan_id",    "head_id",      "schedule"};
std::unordered_map<std::string, uint8_t> data::Journal_tableBase::nameToNum = {
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

std::string data::SubjectBase::tableName          = "subject";
std::vector<data::Type> data::SubjectBase::types  = {data::Type::INT,
                                                     data::Type::STRING};
std::vector<std::string> data::SubjectBase::names = {"id", "name"};
std::unordered_map<std::string, uint8_t> data::SubjectBase::nameToNum = {
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
std::vector<std::string> data::MarkBase::names = {
    "id", "mark_value", "student_id", "lesson_id", "journal_table_id"};
std::unordered_map<std::string, uint8_t> data::MarkBase::nameToNum = {
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
std::vector<std::string> data::PlanBase::names = {"id", "subject_id", "name",
                                                  "url"};
std::unordered_map<std::string, uint8_t> data::PlanBase::nameToNum = {
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
std::vector<std::string> data::ThemeBase::names = {"id", "plan_id", "name",
                                                   "hour_count"};
std::unordered_map<std::string, uint8_t> data::ThemeBase::nameToNum = {
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

std::string data::FileBase::tableName          = "file";
std::vector<data::Type> data::FileBase::types  = {data::Type::INT,
                                                  data::Type::INT};
std::vector<std::string> data::FileBase::names = {"id", "num"};
std::unordered_map<std::string, uint8_t> data::FileBase::nameToNum = {
    {"id",  0},
    {"num", 1}
};

void
data::FileBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&num);
}

std::string data::Safe_fileBase::tableName          = "safe_file";
std::vector<data::Type> data::Safe_fileBase::types  = {data::Type::INT,
                                                       data::Type::INT};
std::vector<std::string> data::Safe_fileBase::names = {"id", "num"};
std::unordered_map<std::string, uint8_t> data::Safe_fileBase::nameToNum = {
    {"id",  0},
    {"num", 1}
};

void
data::Safe_fileBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&num);
}

std::string data::HolidayBase::tableName         = "holiday";
std::vector<data::Type> data::HolidayBase::types = {
    data::Type::INT, data::Type::INT, data::Type::STRING};
std::vector<std::string> data::HolidayBase::names = {"id", "school_id",
                                                     "date_val"};
std::unordered_map<std::string, uint8_t> data::HolidayBase::nameToNum = {
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

std::string data::CompetitionBase::tableName         = "competition";
std::vector<data::Type> data::CompetitionBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING,
    data::Type::STRING};
std::vector<std::string> data::CompetitionBase::names = {
    "id", "name", "start_time", "end_time"};
std::unordered_map<std::string, uint8_t> data::CompetitionBase::nameToNum = {
    {"id",         0},
    {"name",       1},
    {"start_time", 2},
    {"end_time",   3}
};

void
data::CompetitionBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&name);
    ptrs[2] = (void*)(&start_time);
    ptrs[3] = (void*)(&end_time);
}

std::string data::User_competitionBase::tableName         = "user_competition";
std::vector<data::Type> data::User_competitionBase::types = {
    data::Type::INT, data::Type::INT, data::Type::INT};
std::vector<std::string> data::User_competitionBase::names = {"id", "user_id",
                                                              "competition_id"};
std::unordered_map<std::string, uint8_t> data::User_competitionBase::nameToNum =
    {
        {"id",             0},
        {"user_id",        1},
        {"competition_id", 2}
};

void
data::User_competitionBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&user_id);
    ptrs[2] = (void*)(&competition_id);
}

std::string data::ProblemBase::tableName         = "problem";
std::vector<data::Type> data::ProblemBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING, data::Type::STRING,
    data::Type::INT, data::Type::INT,    data::Type::INT,    data::Type::INT};
std::vector<std::string> data::ProblemBase::names = {
    "id",         "name",          "nickname",   "checker_name",
    "test_count", "example_count", "time_limit", "memory_limit"};
std::unordered_map<std::string, uint8_t> data::ProblemBase::nameToNum = {
    {"id",            0},
    {"name",          1},
    {"nickname",      2},
    {"checker_name",  3},
    {"test_count",    4},
    {"example_count", 5},
    {"time_limit",    6},
    {"memory_limit",  7}
};

void
data::ProblemBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&name);
    ptrs[2] = (void*)(&nickname);
    ptrs[3] = (void*)(&checker_name);
    ptrs[4] = (void*)(&test_count);
    ptrs[5] = (void*)(&example_count);
    ptrs[6] = (void*)(&time_limit);
    ptrs[7] = (void*)(&memory_limit);
}

std::string data::Competition_problemBase::tableName = "competition_problem";
std::vector<data::Type> data::Competition_problemBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::INT, data::Type::INT};
std::vector<std::string> data::Competition_problemBase::names = {
    "id", "name", "competition_id", "problem_id"};
std::unordered_map<std::string, uint8_t>
    data::Competition_problemBase::nameToNum = {
        {"id",             0},
        {"name",           1},
        {"competition_id", 2},
        {"problem_id",     3}
};

void
data::Competition_problemBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&name);
    ptrs[2] = (void*)(&competition_id);
    ptrs[3] = (void*)(&problem_id);
}

std::string data::SubmissionBase::tableName         = "submission";
std::vector<data::Type> data::SubmissionBase::types = {
    data::Type::INT,    data::Type::INT, data::Type::INT,   data::Type::STRING,
    data::Type::STRING, data::Type::INT, data::Type::STRING};
std::vector<std::string> data::SubmissionBase::names = {
    "id",      "user_id", "problem_id", "date_val",
    "verdict", "test",    "source_name"};
std::unordered_map<std::string, uint8_t> data::SubmissionBase::nameToNum = {
    {"id",          0},
    {"user_id",     1},
    {"problem_id",  2},
    {"date_val",    3},
    {"verdict",     4},
    {"test",        5},
    {"source_name", 6}
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
    ptrs[6] = (void*)(&source_name);
}

std::string data::QuestionBase::tableName         = "question";
std::vector<data::Type> data::QuestionBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING,
    data::Type::INT, data::Type::INT,    data::Type::STRING};
std::vector<std::string> data::QuestionBase::names = {
    "id", "name", "nickname", "type", "weight", "jury_answer"};
std::unordered_map<std::string, uint8_t> data::QuestionBase::nameToNum = {
    {"id",          0},
    {"name",        1},
    {"nickname",    2},
    {"type",        3},
    {"weight",      4},
    {"jury_answer", 5}
};

void
data::QuestionBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&name);
    ptrs[2] = (void*)(&nickname);
    ptrs[3] = (void*)(&type);
    ptrs[4] = (void*)(&weight);
    ptrs[5] = (void*)(&jury_answer);
}

std::string data::Competition_questionBase::tableName = "competition_question";
std::vector<data::Type> data::Competition_questionBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::INT, data::Type::INT};
std::vector<std::string> data::Competition_questionBase::names = {
    "id", "name", "competition_id", "question_id"};
std::unordered_map<std::string, uint8_t>
    data::Competition_questionBase::nameToNum = {
        {"id",             0},
        {"name",           1},
        {"competition_id", 2},
        {"question_id",    3}
};

void
data::Competition_questionBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&name);
    ptrs[2] = (void*)(&competition_id);
    ptrs[3] = (void*)(&question_id);
}

std::string data::AnswerBase::tableName         = "answer";
std::vector<data::Type> data::AnswerBase::types = {
    data::Type::INT,    data::Type::INT, data::Type::INT,   data::Type::STRING,
    data::Type::STRING, data::Type::INT, data::Type::STRING};
std::vector<std::string> data::AnswerBase::names = {
    "id", "user_id", "question_id", "time", "verdict", "weight", "value"};
std::unordered_map<std::string, uint8_t> data::AnswerBase::nameToNum = {
    {"id",          0},
    {"user_id",     1},
    {"question_id", 2},
    {"time",        3},
    {"verdict",     4},
    {"weight",      5},
    {"value",       6}
};

void
data::AnswerBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&user_id);
    ptrs[2] = (void*)(&question_id);
    ptrs[3] = (void*)(&time);
    ptrs[4] = (void*)(&verdict);
    ptrs[5] = (void*)(&weight);
    ptrs[6] = (void*)(&value);
}

std::string data::File_exchangeBase::tableName         = "file_exchange";
std::vector<data::Type> data::File_exchangeBase::types = {
    data::Type::INT,    data::Type::STRING, data::Type::STRING,
    data::Type::STRING, data::Type::STRING, data::Type::STRING};
std::vector<std::string> data::File_exchangeBase::names = {
    "id", "type", "direction", "index", "name", "extension"};
std::unordered_map<std::string, uint8_t> data::File_exchangeBase::nameToNum = {
    {"id",        0},
    {"type",      1},
    {"direction", 2},
    {"index",     3},
    {"name",      4},
    {"extension", 5}
};

void
data::File_exchangeBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&type);
    ptrs[2] = (void*)(&direction);
    ptrs[3] = (void*)(&index);
    ptrs[4] = (void*)(&name);
    ptrs[5] = (void*)(&extension);
}
