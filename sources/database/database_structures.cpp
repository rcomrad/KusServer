#include "database_structures.hpp"

std::string data::AnswerBase::tableName         = {"answer"};
std::vector<data::Type> data::AnswerBase::types = {
    data::Type::INT,    data::Type::INT, data::Type::INT,   data::Type::STRING,
    data::Type::STRING, data::Type::INT, data::Type::STRING};
std::vector<std::string> data::AnswerBase::columnNames = {
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
    ptrs[1] = (void*)(&userID);
    ptrs[2] = (void*)(&questionID);
    ptrs[3] = (void*)(&time);
    ptrs[4] = (void*)(&verdict);
    ptrs[5] = (void*)(&weight);
    ptrs[6] = (void*)(&value);
}

std::string data::CompetitionBase::tableName         = {"competition"};
std::vector<data::Type> data::CompetitionBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING,
    data::Type::STRING};
std::vector<std::string> data::CompetitionBase::columnNames = {
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
    ptrs[2] = (void*)(&startTime);
    ptrs[3] = (void*)(&endTime);
}

std::string data::CompetitionProblemBase::tableName = {"competition_problem"};
std::vector<data::Type> data::CompetitionProblemBase::types = {
    data::Type::INT, data::Type::INT, data::Type::INT, data::Type::STRING};
std::vector<std::string> data::CompetitionProblemBase::columnNames = {
    "id", "competition_id", "problem_id", "name"};
std::unordered_map<std::string, uint8_t>
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

std::string data::CompetitionQuestionBase::tableName = {"competition_question"};
std::vector<data::Type> data::CompetitionQuestionBase::types = {
    data::Type::INT, data::Type::INT, data::Type::INT, data::Type::STRING};
std::vector<std::string> data::CompetitionQuestionBase::columnNames = {
    "id", "competition_id", "question_id", "name"};
std::unordered_map<std::string, uint8_t>
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

std::string data::CompetitionUserBase::tableName         = {"competition_user"};
std::vector<data::Type> data::CompetitionUserBase::types = {
    data::Type::INT, data::Type::INT, data::Type::INT};
std::vector<std::string> data::CompetitionUserBase::columnNames = {
    "id", "competition_id", "user_id"};
std::unordered_map<std::string, uint8_t> data::CompetitionUserBase::nameToNum =
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

std::string data::DummyBase::tableName                = {"dummy"};
std::vector<data::Type> data::DummyBase::types        = {data::Type::INT};
std::vector<std::string> data::DummyBase::columnNames = {"id"};
std::unordered_map<std::string, uint8_t> data::DummyBase::nameToNum = {
    {"id", 0}
};

void
data::DummyBase::reset()
{
    ptrs[0] = (void*)(&id);
}

std::string data::FileBase::tableName                = {"file"};
std::vector<data::Type> data::FileBase::types        = {data::Type::INT,
                                                        data::Type::INT};
std::vector<std::string> data::FileBase::columnNames = {"id", "num"};
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

std::string data::FileExchangeBase::tableName         = {"file_exchange"};
std::vector<data::Type> data::FileExchangeBase::types = {
    data::Type::INT,    data::Type::STRING, data::Type::STRING,
    data::Type::STRING, data::Type::STRING, data::Type::STRING};
std::vector<std::string> data::FileExchangeBase::columnNames = {
    "id", "type", "direction", "index", "name", "extension"};
std::unordered_map<std::string, uint8_t> data::FileExchangeBase::nameToNum = {
    {"id",        0},
    {"type",      1},
    {"direction", 2},
    {"index",     3},
    {"name",      4},
    {"extension", 5}
};

void
data::FileExchangeBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&type);
    ptrs[2] = (void*)(&direction);
    ptrs[3] = (void*)(&index);
    ptrs[4] = (void*)(&name);
    ptrs[5] = (void*)(&extension);
}

std::string data::GradeBase::tableName         = {"grade"};
std::vector<data::Type> data::GradeBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::INT};
std::vector<std::string> data::GradeBase::columnNames = {"id", "name",
                                                         "head_id"};
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
    ptrs[2] = (void*)(&headID);
}

std::string data::GradeStudentBase::tableName         = {"grade_student"};
std::vector<data::Type> data::GradeStudentBase::types = {
    data::Type::INT, data::Type::INT, data::Type::INT};
std::vector<std::string> data::GradeStudentBase::columnNames = {
    "id", "grade_id", "student_id"};
std::unordered_map<std::string, uint8_t> data::GradeStudentBase::nameToNum = {
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

std::string data::GroupBase::tableName         = {"group"};
std::vector<data::Type> data::GroupBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::INT};
std::vector<std::string> data::GroupBase::columnNames = {"id", "name",
                                                         "grade_id"};
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
    ptrs[2] = (void*)(&gradeID);
}

std::string data::GroupStudentBase::tableName         = {"group_student"};
std::vector<data::Type> data::GroupStudentBase::types = {
    data::Type::INT, data::Type::INT, data::Type::INT};
std::vector<std::string> data::GroupStudentBase::columnNames = {
    "id", "group_id", "student_id"};
std::unordered_map<std::string, uint8_t> data::GroupStudentBase::nameToNum = {
    {"id",         0},
    {"group_id",   1},
    {"student_id", 2}
};

void
data::GroupStudentBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&groupID);
    ptrs[2] = (void*)(&studentID);
}

std::string data::HolidayBase::tableName         = {"holiday"};
std::vector<data::Type> data::HolidayBase::types = {
    data::Type::INT, data::Type::INT, data::Type::STRING};
std::vector<std::string> data::HolidayBase::columnNames = {"id", "school_id",
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
    ptrs[1] = (void*)(&schoolID);
    ptrs[2] = (void*)(&dateVal);
}

std::string data::JournalTableBase::tableName         = {"journal_table"};
std::vector<data::Type> data::JournalTableBase::types = {
    data::Type::INT,  data::Type::INT, data::Type::INT,
    data::Type::BOOL, data::Type::INT, data::Type::INT,
    data::Type::INT,  data::Type::INT, data::Type::STRING};
std::vector<std::string> data::JournalTableBase::columnNames = {
    "id",         "teacher_id", "methodist_id", "is_group", "group_id",
    "subject_id", "plan_id",    "head_id",      "schedule"};
std::unordered_map<std::string, uint8_t> data::JournalTableBase::nameToNum = {
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
data::JournalTableBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&teacherID);
    ptrs[2] = (void*)(&methodistID);
    ptrs[3] = (void*)(&isGroup);
    ptrs[4] = (void*)(&groupID);
    ptrs[5] = (void*)(&subjectID);
    ptrs[6] = (void*)(&planID);
    ptrs[7] = (void*)(&headID);
    ptrs[8] = (void*)(&schedule);
}

std::string data::LessonBase::tableName         = {"lesson"};
std::vector<data::Type> data::LessonBase::types = {
    data::Type::INT, data::Type::INT,    data::Type::STRING,
    data::Type::INT, data::Type::STRING, data::Type::STRING};
std::vector<std::string> data::LessonBase::columnNames = {
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
    ptrs[1] = (void*)(&themeID);
    ptrs[2] = (void*)(&dateVal);
    ptrs[3] = (void*)(&journalTableID);
    ptrs[4] = (void*)(&homework);
    ptrs[5] = (void*)(&control);
}

std::string data::MarkBase::tableName         = {"mark"};
std::vector<data::Type> data::MarkBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::INT, data::Type::INT,
    data::Type::INT};
std::vector<std::string> data::MarkBase::columnNames = {
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
    ptrs[1] = (void*)(&markValue);
    ptrs[2] = (void*)(&studentID);
    ptrs[3] = (void*)(&lessonID);
    ptrs[4] = (void*)(&journalTableID);
}

std::string data::PlanBase::tableName         = {"plan"};
std::vector<data::Type> data::PlanBase::types = {
    data::Type::INT, data::Type::INT, data::Type::STRING, data::Type::STRING};
std::vector<std::string> data::PlanBase::columnNames = {"id", "subject_id",
                                                        "name", "url"};
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
    ptrs[1] = (void*)(&subjectID);
    ptrs[2] = (void*)(&name);
    ptrs[3] = (void*)(&url);
}

std::string data::ProblemBase::tableName         = {"problem"};
std::vector<data::Type> data::ProblemBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING, data::Type::STRING,
    data::Type::INT, data::Type::INT,    data::Type::INT,    data::Type::INT};
std::vector<std::string> data::ProblemBase::columnNames = {
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
    ptrs[3] = (void*)(&checkerName);
    ptrs[4] = (void*)(&testCount);
    ptrs[5] = (void*)(&exampleCount);
    ptrs[6] = (void*)(&timeLimit);
    ptrs[7] = (void*)(&memoryLimit);
}

std::string data::QuestionBase::tableName         = {"question"};
std::vector<data::Type> data::QuestionBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING,
    data::Type::INT, data::Type::INT,    data::Type::STRING};
std::vector<std::string> data::QuestionBase::columnNames = {
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
    ptrs[5] = (void*)(&juryAnswer);
}

std::string data::RoleBase::tableName                = {"role"};
std::vector<data::Type> data::RoleBase::types        = {data::Type::INT,
                                                        data::Type::STRING};
std::vector<std::string> data::RoleBase::columnNames = {"id", "name"};
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

std::string data::SafeFileBase::tableName                = {"safe_file"};
std::vector<data::Type> data::SafeFileBase::types        = {data::Type::INT,
                                                            data::Type::INT};
std::vector<std::string> data::SafeFileBase::columnNames = {"id", "num"};
std::unordered_map<std::string, uint8_t> data::SafeFileBase::nameToNum = {
    {"id",  0},
    {"num", 1}
};

void
data::SafeFileBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&num);
}

std::string data::SchoolBase::tableName         = {"school"};
std::vector<data::Type> data::SchoolBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING,
    data::Type::STRING};
std::vector<std::string> data::SchoolBase::columnNames = {
    "id", "full_name", "short_name", "start_date"};
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
    ptrs[1] = (void*)(&fullName);
    ptrs[2] = (void*)(&shortName);
    ptrs[3] = (void*)(&startDate);
}

std::string data::SubjectBase::tableName                = {"subject"};
std::vector<data::Type> data::SubjectBase::types        = {data::Type::INT,
                                                           data::Type::STRING};
std::vector<std::string> data::SubjectBase::columnNames = {"id", "name"};
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

std::string data::SubmissionBase::tableName         = {"submission"};
std::vector<data::Type> data::SubmissionBase::types = {
    data::Type::INT,    data::Type::INT, data::Type::INT,   data::Type::STRING,
    data::Type::STRING, data::Type::INT, data::Type::STRING};
std::vector<std::string> data::SubmissionBase::columnNames = {
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
    ptrs[1] = (void*)(&userID);
    ptrs[2] = (void*)(&problemID);
    ptrs[3] = (void*)(&dateVal);
    ptrs[4] = (void*)(&verdict);
    ptrs[5] = (void*)(&test);
    ptrs[6] = (void*)(&sourceName);
}

std::string data::ThemeBase::tableName         = {"theme"};
std::vector<data::Type> data::ThemeBase::types = {
    data::Type::INT, data::Type::INT, data::Type::STRING, data::Type::INT};
std::vector<std::string> data::ThemeBase::columnNames = {"id", "plan_id",
                                                         "name", "hour_count"};
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
    ptrs[1] = (void*)(&planID);
    ptrs[2] = (void*)(&name);
    ptrs[3] = (void*)(&hourCount);
}

std::string data::UserBase::tableName         = {"user"};
std::vector<data::Type> data::UserBase::types = {
    data::Type::INT,    data::Type::STRING, data::Type::STRING,
    data::Type::STRING, data::Type::STRING, data::Type::INT,
    data::Type::INT};
std::vector<std::string> data::UserBase::columnNames = {
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
    ptrs[5] = (void*)(&schoolID);
    ptrs[6] = (void*)(&roleID);
}
