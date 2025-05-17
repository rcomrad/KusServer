#include "database_structures.hpp"

str::String data::AnswerBase::tableName         = {"answer"};
std::vector<data::Type> data::AnswerBase::types = {
    data::Type::INT,    data::Type::INT,    data::Type::INT,
    data::Type::STRING, data::Type::STRING, data::Type::FLOAT,
    data::Type::STRING};
std::vector<str::String> data::AnswerBase::columnNames = {
    "id", "user_id", "question_id", "time", "verdict", "weight", "value"};
std::unordered_map<str::String, uint8_t> data::AnswerBase::nameToNum = {
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
    ptrs[1] = (void*)(&userID);
    ptrs[2] = (void*)(&questionID);
    ptrs[3] = (void*)(&time);
    ptrs[4] = (void*)(&verdict);
    ptrs[5] = (void*)(&weight);
    ptrs[6] = (void*)(&value);
}

str::String data::CompetitionBase::tableName         = {"competition"};
std::vector<data::Type> data::CompetitionBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING,
    data::Type::STRING};
std::vector<str::String> data::CompetitionBase::columnNames = {
    "id", "name", "start_time", "end_time"};
std::unordered_map<str::String, uint8_t> data::CompetitionBase::nameToNum = {
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
    ptrs[2] = (void*)(&startTime);
    ptrs[3] = (void*)(&endTime);
}

str::String data::CompetitionProblemBase::tableName = {"competition_problem"};
std::vector<data::Type> data::CompetitionProblemBase::types = {
    data::Type::INT, data::Type::INT, data::Type::INT, data::Type::STRING};
std::vector<str::String> data::CompetitionProblemBase::columnNames = {
    "id", "competition_id", "problem_id", "name"};
std::unordered_map<str::String, uint8_t>
    data::CompetitionProblemBase::nameToNum = {
        {"id",             0},
        {"competition_id", 1},
        {"problem_id",     2},
        {"name",           3}
};

void
data::CompetitionProblemBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&competitionID);
    ptrs[2] = (void*)(&problemID);
    ptrs[3] = (void*)(&name);
}

str::String data::CompetitionQuestionBase::tableName = {"competition_question"};
std::vector<data::Type> data::CompetitionQuestionBase::types = {
    data::Type::INT, data::Type::INT, data::Type::INT, data::Type::STRING};
std::vector<str::String> data::CompetitionQuestionBase::columnNames = {
    "id", "competition_id", "question_id", "name"};
std::unordered_map<str::String, uint8_t>
    data::CompetitionQuestionBase::nameToNum = {
        {"id",             0},
        {"competition_id", 1},
        {"question_id",    2},
        {"name",           3}
};

void
data::CompetitionQuestionBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&competitionID);
    ptrs[2] = (void*)(&questionID);
    ptrs[3] = (void*)(&name);
}

str::String data::CompetitionUserBase::tableName         = {"competition_user"};
std::vector<data::Type> data::CompetitionUserBase::types = {
    data::Type::INT, data::Type::INT, data::Type::INT};
std::vector<str::String> data::CompetitionUserBase::columnNames = {
    "id", "competition_id", "user_id"};
std::unordered_map<str::String, uint8_t> data::CompetitionUserBase::nameToNum =
    {
        {"id",             0},
        {"competition_id", 1},
        {"user_id",        2}
};

void
data::CompetitionUserBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&competitionID);
    ptrs[2] = (void*)(&userID);
}

str::String data::DummyBase::tableName                = {"dummy"};
std::vector<data::Type> data::DummyBase::types        = {data::Type::INT};
std::vector<str::String> data::DummyBase::columnNames = {"id"};
std::unordered_map<str::String, uint8_t> data::DummyBase::nameToNum = {
    {"id", 0}
};

void
data::DummyBase::reset()
{
    ptrs[0] = (void*)(&id);
}

str::String data::FieldBase::tableName         = {"field"};
std::vector<data::Type> data::FieldBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING, data::Type::STRING,
    data::Type::STRING};
std::vector<str::String> data::FieldBase::columnNames = {"id", "type", "info",
                                                         "name", "label"};
std::unordered_map<str::String, uint8_t> data::FieldBase::nameToNum = {
    {"id",    0},
    {"type",  1},
    {"info",  2},
    {"name",  3},
    {"label", 4}
};

void
data::FieldBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&type);
    ptrs[2] = (void*)(&info);
    ptrs[3] = (void*)(&name);
    ptrs[4] = (void*)(&label);
}

str::String data::FieldFormBase::tableName         = {"field_form"};
std::vector<data::Type> data::FieldFormBase::types = {
    data::Type::INT, data::Type::INT, data::Type::INT};
std::vector<str::String> data::FieldFormBase::columnNames = {"id", "field_id",
                                                             "form_id"};
std::unordered_map<str::String, uint8_t> data::FieldFormBase::nameToNum = {
    {"id",       0},
    {"field_id", 1},
    {"form_id",  2}
};

void
data::FieldFormBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&fieldID);
    ptrs[2] = (void*)(&formID);
}

str::String data::FileBase::tableName                = {"file"};
std::vector<data::Type> data::FileBase::types        = {data::Type::INT,
                                                        data::Type::INT};
std::vector<str::String> data::FileBase::columnNames = {"id", "num"};
std::unordered_map<str::String, uint8_t> data::FileBase::nameToNum = {
    {"id",  0},
    {"num", 1}
};

void
data::FileBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&num);
}

str::String data::FormBase::tableName         = {"form"};
std::vector<data::Type> data::FormBase::types = {
    data::Type::INT,    data::Type::STRING, data::Type::STRING,
    data::Type::STRING, data::Type::STRING, data::Type::INT};
std::vector<str::String> data::FormBase::columnNames = {
    "id", "module", "userName", "techName", "role_str", "role_id"};
std::unordered_map<str::String, uint8_t> data::FormBase::nameToNum = {
    {"id",       0},
    {"module",   1},
    {"userName", 2},
    {"techName", 3},
    {"role_str", 4},
    {"role_id",  5}
};

void
data::FormBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&module);
    ptrs[2] = (void*)(&userName);
    ptrs[3] = (void*)(&techName);
    ptrs[4] = (void*)(&roleStr);
    ptrs[5] = (void*)(&roleID);
}

str::String data::GradeBase::tableName         = {"grade"};
std::vector<data::Type> data::GradeBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::INT, data::Type::BOOL};
std::vector<str::String> data::GradeBase::columnNames = {"id", "name",
                                                         "head_id", "is_group"};
std::unordered_map<str::String, uint8_t> data::GradeBase::nameToNum = {
    {"id",       0},
    {"name",     1},
    {"head_id",  2},
    {"is_group", 3}
};

void
data::GradeBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&name);
    ptrs[2] = (void*)(&headID);
    ptrs[3] = (void*)(&isGroup);
}

str::String data::GradeStudentBase::tableName         = {"grade_student"};
std::vector<data::Type> data::GradeStudentBase::types = {
    data::Type::INT, data::Type::INT, data::Type::INT};
std::vector<str::String> data::GradeStudentBase::columnNames = {
    "id", "grade_id", "student_id"};
std::unordered_map<str::String, uint8_t> data::GradeStudentBase::nameToNum = {
    {"id",         0},
    {"grade_id",   1},
    {"student_id", 2}
};

void
data::GradeStudentBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&gradeID);
    ptrs[2] = (void*)(&studentID);
}

str::String data::HolidayBase::tableName         = {"holiday"};
std::vector<data::Type> data::HolidayBase::types = {
    data::Type::INT, data::Type::INT, data::Type::STRING};
std::vector<str::String> data::HolidayBase::columnNames = {"id", "school_id",
                                                           "date_val"};
std::unordered_map<str::String, uint8_t> data::HolidayBase::nameToNum = {
    {"id",        0},
    {"school_id", 1},
    {"date_val",  2}
};

void
data::HolidayBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&schoolID);
    ptrs[2] = (void*)(&dateVal);
}

str::String data::JournalTableBase::tableName         = {"journal_table"};
std::vector<data::Type> data::JournalTableBase::types = {
    data::Type::INT, data::Type::INT, data::Type::INT, data::Type::INT,
    data::Type::INT, data::Type::INT, data::Type::INT, data::Type::STRING};
std::vector<str::String> data::JournalTableBase::columnNames = {
    "id",         "teacher_id", "methodist_id", "grade_id",
    "subject_id", "plan_id",    "head_id",      "schedule"};
std::unordered_map<str::String, uint8_t> data::JournalTableBase::nameToNum = {
    {"id",           0},
    {"teacher_id",   1},
    {"methodist_id", 2},
    {"grade_id",     3},
    {"subject_id",   4},
    {"plan_id",      5},
    {"head_id",      6},
    {"schedule",     7}
};

void
data::JournalTableBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&teacherID);
    ptrs[2] = (void*)(&methodistID);
    ptrs[3] = (void*)(&gradeID);
    ptrs[4] = (void*)(&subjectID);
    ptrs[5] = (void*)(&planID);
    ptrs[6] = (void*)(&headID);
    ptrs[7] = (void*)(&schedule);
}

str::String data::LessonBase::tableName         = {"lesson"};
std::vector<data::Type> data::LessonBase::types = {
    data::Type::INT, data::Type::INT,    data::Type::STRING,
    data::Type::INT, data::Type::STRING, data::Type::STRING};
std::vector<str::String> data::LessonBase::columnNames = {
    "id", "theme_id", "date_val", "journal_table_id", "homework", "control"};
std::unordered_map<str::String, uint8_t> data::LessonBase::nameToNum = {
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
    ptrs[1] = (void*)(&themeID);
    ptrs[2] = (void*)(&dateVal);
    ptrs[3] = (void*)(&journalTableID);
    ptrs[4] = (void*)(&homework);
    ptrs[5] = (void*)(&control);
}

str::String data::MarkBase::tableName         = {"mark"};
std::vector<data::Type> data::MarkBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::INT, data::Type::INT,
    data::Type::INT};
std::vector<str::String> data::MarkBase::columnNames = {
    "id", "mark_value", "student_id", "lesson_id", "journal_table_id"};
std::unordered_map<str::String, uint8_t> data::MarkBase::nameToNum = {
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
    ptrs[1] = (void*)(&markValue);
    ptrs[2] = (void*)(&studentID);
    ptrs[3] = (void*)(&lessonID);
    ptrs[4] = (void*)(&journalTableID);
}

str::String data::PlanBase::tableName         = {"plan"};
std::vector<data::Type> data::PlanBase::types = {
    data::Type::INT, data::Type::INT, data::Type::STRING, data::Type::STRING};
std::vector<str::String> data::PlanBase::columnNames = {"id", "subject_id",
                                                        "name", "url"};
std::unordered_map<str::String, uint8_t> data::PlanBase::nameToNum = {
    {"id",         0},
    {"subject_id", 1},
    {"name",       2},
    {"url",        3}
};

void
data::PlanBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&subjectID);
    ptrs[2] = (void*)(&name);
    ptrs[3] = (void*)(&url);
}

str::String data::ProblemBase::tableName         = {"problem"};
std::vector<data::Type> data::ProblemBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING, data::Type::STRING,
    data::Type::INT, data::Type::INT,    data::Type::INT,    data::Type::INT};
std::vector<str::String> data::ProblemBase::columnNames = {
    "id",         "name",          "nickname",   "checker_name",
    "test_count", "example_count", "time_limit", "memory_limit"};
std::unordered_map<str::String, uint8_t> data::ProblemBase::nameToNum = {
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
    ptrs[3] = (void*)(&checkerName);
    ptrs[4] = (void*)(&testCount);
    ptrs[5] = (void*)(&exampleCount);
    ptrs[6] = (void*)(&timeLimit);
    ptrs[7] = (void*)(&memoryLimit);
}

str::String data::QuestionBase::tableName         = {"question"};
std::vector<data::Type> data::QuestionBase::types = {
    data::Type::INT,    data::Type::STRING, data::Type::STRING,
    data::Type::STRING, data::Type::FLOAT,  data::Type::STRING};
std::vector<str::String> data::QuestionBase::columnNames = {
    "id", "name", "nickname", "type", "weight", "jury_answer"};
std::unordered_map<str::String, uint8_t> data::QuestionBase::nameToNum = {
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
    ptrs[5] = (void*)(&juryAnswer);
}

str::String data::RoleBase::tableName                = {"role"};
std::vector<data::Type> data::RoleBase::types        = {data::Type::INT,
                                                        data::Type::STRING};
std::vector<str::String> data::RoleBase::columnNames = {"id", "name"};
std::unordered_map<str::String, uint8_t> data::RoleBase::nameToNum = {
    {"id",   0},
    {"name", 1}
};

void
data::RoleBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&name);
}

str::String data::SafeFileBase::tableName                = {"safe_file"};
std::vector<data::Type> data::SafeFileBase::types        = {data::Type::INT,
                                                            data::Type::INT};
std::vector<str::String> data::SafeFileBase::columnNames = {"id", "num"};
std::unordered_map<str::String, uint8_t> data::SafeFileBase::nameToNum = {
    {"id",  0},
    {"num", 1}
};

void
data::SafeFileBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&num);
}

str::String data::SchoolBase::tableName         = {"school"};
std::vector<data::Type> data::SchoolBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING,
    data::Type::STRING};
std::vector<str::String> data::SchoolBase::columnNames = {
    "id", "full_name", "short_name", "start_date"};
std::unordered_map<str::String, uint8_t> data::SchoolBase::nameToNum = {
    {"id",         0},
    {"full_name",  1},
    {"short_name", 2},
    {"start_date", 3}
};

void
data::SchoolBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&fullName);
    ptrs[2] = (void*)(&shortName);
    ptrs[3] = (void*)(&startDate);
}

str::String data::SubjectBase::tableName                = {"subject"};
std::vector<data::Type> data::SubjectBase::types        = {data::Type::INT,
                                                           data::Type::STRING};
std::vector<str::String> data::SubjectBase::columnNames = {"id", "name"};
std::unordered_map<str::String, uint8_t> data::SubjectBase::nameToNum = {
    {"id",   0},
    {"name", 1}
};

void
data::SubjectBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&name);
}

str::String data::SubmissionBase::tableName         = {"submission"};
std::vector<data::Type> data::SubmissionBase::types = {
    data::Type::INT,    data::Type::INT, data::Type::INT,   data::Type::STRING,
    data::Type::STRING, data::Type::INT, data::Type::STRING};
std::vector<str::String> data::SubmissionBase::columnNames = {
    "id",      "user_id", "problem_id", "date_val",
    "verdict", "test",    "source_name"};
std::unordered_map<str::String, uint8_t> data::SubmissionBase::nameToNum = {
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
    ptrs[1] = (void*)(&userID);
    ptrs[2] = (void*)(&problemID);
    ptrs[3] = (void*)(&dateVal);
    ptrs[4] = (void*)(&verdict);
    ptrs[5] = (void*)(&test);
    ptrs[6] = (void*)(&sourceName);
}

str::String data::ThemeBase::tableName         = {"theme"};
std::vector<data::Type> data::ThemeBase::types = {
    data::Type::INT, data::Type::INT, data::Type::STRING, data::Type::INT};
std::vector<str::String> data::ThemeBase::columnNames = {"id", "plan_id",
                                                         "name", "hour_count"};
std::unordered_map<str::String, uint8_t> data::ThemeBase::nameToNum = {
    {"id",         0},
    {"plan_id",    1},
    {"name",       2},
    {"hour_count", 3}
};

void
data::ThemeBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&planID);
    ptrs[2] = (void*)(&name);
    ptrs[3] = (void*)(&hourCount);
}

str::String data::TokenBase::tableName         = {"token"};
std::vector<data::Type> data::TokenBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING,
    data::Type::INT, data::Type::INT,    data::Type::STRING};
std::vector<str::String> data::TokenBase::columnNames = {
    "id", "start_time", "value", "user_id", "user_role", "user_ip"};
std::unordered_map<str::String, uint8_t> data::TokenBase::nameToNum = {
    {"id",         0},
    {"start_time", 1},
    {"value",      2},
    {"user_id",    3},
    {"user_role",  4},
    {"user_ip",    5}
};

void
data::TokenBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&startTime);
    ptrs[2] = (void*)(&value);
    ptrs[3] = (void*)(&userID);
    ptrs[4] = (void*)(&userRole);
    ptrs[5] = (void*)(&userIp);
}

str::String data::UserBase::tableName         = {"user"};
std::vector<data::Type> data::UserBase::types = {
    data::Type::INT,    data::Type::STRING, data::Type::STRING,
    data::Type::STRING, data::Type::STRING, data::Type::STRING,
    data::Type::STRING, data::Type::INT,    data::Type::STRING,
    data::Type::INT,    data::Type::INT};
std::vector<str::String> data::UserBase::columnNames = {
    "id",      "login",     "password", "email",  "last_login", "name",
    "surname", "school_id", "key",      "status", "role_id"};
std::unordered_map<str::String, uint8_t> data::UserBase::nameToNum = {
    {"id",         0 },
    {"login",      1 },
    {"password",   2 },
    {"email",      3 },
    {"last_login", 4 },
    {"name",       5 },
    {"surname",    6 },
    {"school_id",  7 },
    {"key",        8 },
    {"status",     9 },
    {"role_id",    10}
};

void
data::UserBase::reset()
{
    ptrs[0]  = (void*)(&id);
    ptrs[1]  = (void*)(&login);
    ptrs[2]  = (void*)(&password);
    ptrs[3]  = (void*)(&email);
    ptrs[4]  = (void*)(&lastLogin);
    ptrs[5]  = (void*)(&name);
    ptrs[6]  = (void*)(&surname);
    ptrs[7]  = (void*)(&schoolID);
    ptrs[8]  = (void*)(&key);
    ptrs[9]  = (void*)(&status);
    ptrs[10] = (void*)(&roleID);
}

str::String data::UserRegistrationBase::tableName = {"user_registration"};
std::vector<data::Type> data::UserRegistrationBase::types = {
    data::Type::INT, data::Type::INT, data::Type::STRING};
std::vector<str::String> data::UserRegistrationBase::columnNames = {
    "id", "user_id", "link"};
std::unordered_map<str::String, uint8_t> data::UserRegistrationBase::nameToNum =
    {
        {"id",      0},
        {"user_id", 1},
        {"link",    2}
};

void
data::UserRegistrationBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&userID);
    ptrs[2] = (void*)(&link);
}
