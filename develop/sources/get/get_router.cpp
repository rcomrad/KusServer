#include "get_router.hpp"

#include "get_handler.hpp"
#include "question_handler.hpp"
#include "user_handler.hpp"

std::unordered_map<std::string, decltype(&get::GetHandler::process<data::Dummy>)> get::GetRouter::mBasicRouter = {
    {"answer",               &get::GetHandler::process<data::Answer>             },
    {"competition",          &get::GetHandler::process<data::Competition>        },
    {"competition_problem",  &get::GetHandler::process<data::CompetitionProblem> },
    {"competition_question", &get::GetHandler::process<data::CompetitionQuestion>},
    {"competition_user",     &get::GetHandler::process<data::CompetitionUser>    },
    {"dummy",                &get::GetHandler::process<data::Dummy>              },
    {"file",                 &get::GetHandler::process<data::File>               },
    {"file_exchange",        &get::GetHandler::process<data::FileExchange>       },
    {"grade",                &get::GetHandler::process<data::Grade>              },
    {"grade_student",        &get::GetHandler::process<data::GradeStudent>       },
    {"group",                &get::GetHandler::process<data::Group>              },
    {"group_student",        &get::GetHandler::process<data::GroupStudent>       },
    {"holiday",              &get::GetHandler::process<data::Holiday>            },
    {"journal_table",        &get::GetHandler::process<data::JournalTable>       },
    {"lesson",               &get::GetHandler::process<data::Lesson>             },
    {"mark",                 &get::GetHandler::process<data::Mark>               },
    {"plan",                 &get::GetHandler::process<data::Plan>               },
    {"problem",              &get::GetHandler::process<data::Problem>            },
    {"question",             &get::GetHandler::process<data::Question>           },
    {"role",                 &get::GetHandler::process<data::Role>               },
    {"safe_file",            &get::GetHandler::process<data::SafeFile>           },
    {"school",               &get::GetHandler::process<data::School>             },
    {"subject",              &get::GetHandler::process<data::Subject>            },
    {"submission",           &get::GetHandler::process<data::Submission>         },
    {"theme",                &get::GetHandler::process<data::Theme>              },
    {"user",                 &get::UserHandler::process                          }
};

std::unordered_map<std::string, decltype(&get::GetHandler::dump<data::Dummy>)> get::GetRouter::mDumpRouter = {
    {"answer",               &get::GetHandler::dump<data::Answer>             },
    {"competition",          &get::GetHandler::dump<data::Competition>        },
    {"competition_problem",  &get::GetHandler::dump<data::CompetitionProblem> },
    {"competition_question", &get::GetHandler::dump<data::CompetitionQuestion>},
    {"competition_user",     &get::GetHandler::dump<data::CompetitionUser>    },
    {"dummy",                &get::GetHandler::dump<data::Dummy>              },
    {"file",                 &get::GetHandler::dump<data::File>               },
    {"file_exchange",        &get::GetHandler::dump<data::FileExchange>       },
    {"grade",                &get::GetHandler::dump<data::Grade>              },
    {"grade_student",        &get::GetHandler::dump<data::GradeStudent>       },
    {"group",                &get::GetHandler::dump<data::Group>              },
    {"group_student",        &get::GetHandler::dump<data::GroupStudent>       },
    {"holiday",              &get::GetHandler::dump<data::Holiday>            },
    {"journal_table",        &get::GetHandler::dump<data::JournalTable>       },
    {"lesson",               &get::GetHandler::dump<data::Lesson>             },
    {"mark",                 &get::GetHandler::dump<data::Mark>               },
    {"plan",                 &get::GetHandler::dump<data::Plan>               },
    {"problem",              &get::GetHandler::dump<data::Problem>            },
    {"question",             &get::GetHandler::dump<data::Question>           },
    {"role",                 &get::GetHandler::dump<data::Role>               },
    {"safe_file",            &get::GetHandler::dump<data::SafeFile>           },
    {"school",               &get::GetHandler::dump<data::School>             },
    {"subject",              &get::GetHandler::dump<data::Subject>            },
    {"submission",           &get::GetHandler::dump<data::Submission>         },
    {"theme",                &get::GetHandler::dump<data::Theme>              },
    {"user",                 &get::GetHandler::dump<data::User>               }
};

std::unordered_map<std::string, std::vector<std::string>> get::GetRouter::mColumnNamesRouter = {
    {"answer",               data::Answer::columnNames             },
    {"competition",          data::Competition::columnNames        },
    {"competition_problem",  data::CompetitionProblem::columnNames },
    {"competition_question", data::CompetitionQuestion::columnNames},
    {"competition_user",     data::CompetitionUser::columnNames    },
    {"dummy",                data::Dummy::columnNames              },
    {"file",                 data::File::columnNames               },
    {"file_exchange",        data::FileExchange::columnNames       },
    {"grade",                data::Grade::columnNames              },
    {"grade_student",        data::GradeStudent::columnNames       },
    {"group",                data::Group::columnNames              },
    {"group_student",        data::GroupStudent::columnNames       },
    {"holiday",              data::Holiday::columnNames            },
    {"journal_table",        data::JournalTable::columnNames       },
    {"lesson",               data::Lesson::columnNames             },
    {"mark",                 data::Mark::columnNames               },
    {"plan",                 data::Plan::columnNames               },
    {"problem",              data::Problem::columnNames            },
    {"question",             data::Question::columnNames           },
    {"role",                 data::Role::columnNames               },
    {"safe_file",            data::SafeFile::columnNames           },
    {"school",               data::School::columnNames             },
    {"subject",              data::Subject::columnNames            },
    {"submission",           data::Submission::columnNames         },
    {"theme",                data::Theme::columnNames              },
    {"user",                 data::User::columnNames               }
};

std::vector<std::string>&
get::GetRouter::columnNamesRouter(const std::string& aName)
{
    auto it = mColumnNamesRouter.find(aName);
    if (it == mColumnNamesRouter.end()) it = mColumnNamesRouter.find("dummy");
    return it->second;
}
