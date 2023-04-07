#include "database_structures.hpp"

#include <cstring>

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

std::string data::Safe_fileBase::tableName         = "safe_file";
std::vector<data::Type> data::Safe_fileBase::types = {data::Type::INT,
                                                      data::Type::INT};
std::unordered_map<std::string, uint8_t> data::Safe_fileBase::columnNames = {
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

std::string data::CompetitionBase::tableName         = "competition";
std::vector<data::Type> data::CompetitionBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING,
    data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::CompetitionBase::columnNames = {
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
std::unordered_map<std::string, uint8_t>
    data::User_competitionBase::columnNames = {
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
std::unordered_map<std::string, uint8_t> data::ProblemBase::columnNames = {
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

std::string data::SubmissionBase::tableName         = "submission";
std::vector<data::Type> data::SubmissionBase::types = {
    data::Type::INT,    data::Type::INT, data::Type::INT,   data::Type::STRING,
    data::Type::STRING, data::Type::INT, data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::SubmissionBase::columnNames = {
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

std::string data::Competition_problemBase::tableName = "competition_problem";
std::vector<data::Type> data::Competition_problemBase::types = {
    data::Type::INT, data::Type::INT, data::Type::INT};
std::unordered_map<std::string, uint8_t>
    data::Competition_problemBase::columnNames = {
        {"id",             0},
        {"competition_id", 1},
        {"problem_id",     2}
};

void
data::Competition_problemBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&competition_id);
    ptrs[2] = (void*)(&problem_id);
}

std::string data::QuestionBase::tableName         = "question";
std::vector<data::Type> data::QuestionBase::types = {
    data::Type::INT, data::Type::STRING, data::Type::STRING, data::Type::INT,
    data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::QuestionBase::columnNames = {
    {"id",          0},
    {"name",        1},
    {"nickname",    2},
    {"type",        3},
    {"jury_answer", 4}
};

void
data::QuestionBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&name);
    ptrs[2] = (void*)(&nickname);
    ptrs[3] = (void*)(&type);
    ptrs[4] = (void*)(&jury_answer);
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

std::string data::Competition_questionBase::tableName = "competition_question";
std::vector<data::Type> data::Competition_questionBase::types = {
    data::Type::INT, data::Type::INT, data::Type::INT};
std::unordered_map<std::string, uint8_t>
    data::Competition_questionBase::columnNames = {
        {"id",             0},
        {"competition_id", 1},
        {"question_id",    2}
};

void
data::Competition_questionBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&competition_id);
    ptrs[2] = (void*)(&question_id);
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

std::string data::Upload_typeBase::tableName         = "upload_type";
std::vector<data::Type> data::Upload_typeBase::types = {
    data::Type::INT,    data::Type::STRING, data::Type::STRING,
    data::Type::STRING, data::Type::STRING, data::Type::STRING};
std::unordered_map<std::string, uint8_t> data::Upload_typeBase::columnNames = {
    {"id",        0},
    {"type",      1},
    {"direction", 2},
    {"index",     3},
    {"name",      4},
    {"extension", 5}
};

void
data::Upload_typeBase::reset()
{
    ptrs[0] = (void*)(&id);
    ptrs[1] = (void*)(&type);
    ptrs[2] = (void*)(&direction);
    ptrs[3] = (void*)(&index);
    ptrs[4] = (void*)(&name);
    ptrs[5] = (void*)(&extension);
}

std::unordered_map<std::string_view, std::vector<std::string>>
    AsteriskHendler::table = {
        {"school",
         {
             "id",
             "full_name",
             "short_name",
             "start_date",
         }                             },
        {"user",
         {
             "id",
             "login",
             "password",
             "name",
             "surname",
             "role_id",
             "school_id",
         }                             },
        {"role",
         {
             "id",
             "name",
         }                             },
        {"grade",
         {
             "id",
             "name",
             "head_id",
         }                             },
        {"grade_student",
         {
             "id",
             "grade_id",
             "student_id",
         }                             },
        {"group",
         {
             "id",
             "name",
             "grade_id",
         }                             },
        {"group_student",
         {
             "id",
             "group_id",
             "student_id",
         }                             },
        {"lesson",
         {
             "id",
             "theme_id",
             "date_val",
             "journal_table_id",
             "homework",
             "control",
         }                             },
        {"journal_table",
         {
             "id",
             "teacher_id",
             "methodist_id",
             "is_group",
             "group_id",
             "subject_id",
             "plan_id",
             "head_id",
             "schedule",
         }                             },
        {"subject",
         {
             "id",
             "name",
         }                             },
        {"mark",
         {
             "id",
             "mark_value",
             "student_id",
             "lesson_id",
             "journal_table_id",
         }                             },
        {"plan",
         {
             "id",
             "subject_id",
             "name",
             "url",
         }                             },
        {"theme",
         {
             "id",
             "plan_id",
             "name",
             "hour_count",
         }                             },
        {"file",
         {
             "id",
             "num",
         }                             },
        {"safe_file",
         {
             "id",
             "num",
         }                             },
        {"holiday",
         {
             "id",
             "school_id",
             "date_val",
         }                             },
        {"competition",
         {
             "id",
             "name",
             "start_time",
             "end_time",
         }                             },
        {"user_competition",
         {
             "id",
             "user_id",
             "competition_id",
         }                             },
        {"problem",
         {
             "id",
             "name",
             "nickname",
             "checker_name",
             "test_count",
             "example_count",
             "time_limit",
             "memory_limit",
         }                             },
        {"submission",
         {
             "id",
             "user_id",
             "problem_id",
             "date_val",
             "verdict",
             "test",
             "source_name",
         }                             },
        {"competition_problem",
         {
             "id",
             "competition_id",
             "problem_id",
         }                             },
        {"question",
         {
             "id",
             "name",
             "nickname",
             "type",
             "jury_answer",
         }                             },
        {"user_answer",
         {
             "id",
             "user_id",
             "question_id",
             "user_answer",
             "time",
             "true_time",
             "is_correct",
         }                             },
        {"competition_question",
         {
             "id",
             "competition_id",
             "question_id",
         }                             },
        {"question_type",
         {
             "id",
             "name",
         }                             },
        {"upload_type",
         {
             "id",
             "type",
             "direction",
             "index",
             "name",
             "extension",
         }                             },
        {"NUN",                  {"id"}}
};
