#include "post_router.hpp"

#include "answer_handler.hpp"
#include "journal_handler.hpp"
#include "mark_handler.hpp"
#include "plan_handler.hpp"
#include "user_handler.hpp"

std::unordered_map<std::string, decltype(&post::PostHandler::postSubrouter<post::PostHandler, data::Dummy>)> post::PostRouter::mProcessRouter = {
    {"answer",               &post::PostHandler::postSubrouter<post::AnswerHandler,  data::Answer>             },
    {"competition",          &post::PostHandler::postSubrouter<post::PostHandler,    data::Competition>        },
    {"competition_problem",  &post::PostHandler::postSubrouter<post::PostHandler,    data::CompetitionProblem> },
    {"competition_question", &post::PostHandler::postSubrouter<post::PostHandler,    data::CompetitionQuestion>},
    {"competition_user",     &post::PostHandler::postSubrouter<post::PostHandler,    data::CompetitionUser>    },
    {"dummy",                &post::PostHandler::postSubrouter<post::PostHandler,    data::Dummy>              },
    {"file",                 &post::PostHandler::postSubrouter<post::PostHandler,    data::File>               },
    {"file_exchange",        &post::PostHandler::postSubrouter<post::PostHandler,    data::FileExchange>       },
    {"grade",                &post::PostHandler::postSubrouter<post::PostHandler,    data::Grade>              },
    {"grade_student",        &post::PostHandler::postSubrouter<post::PostHandler,    data::GradeStudent>       },
    {"group",                &post::PostHandler::postSubrouter<post::PostHandler,    data::Group>              },
    {"group_student",        &post::PostHandler::postSubrouter<post::PostHandler,    data::GroupStudent>       },
    {"holiday",              &post::PostHandler::postSubrouter<post::PostHandler,    data::Holiday>            },
    {"journal_table",        &post::PostHandler::postSubrouter<post::JournalHandler, data::JournalTable>       },
    {"lesson",               &post::PostHandler::postSubrouter<post::PostHandler,    data::Lesson>             },
    {"mark",                 &post::PostHandler::postSubrouter<post::MarkHandler,    data::Mark>               },
    {"plan",                 &post::PostHandler::postSubrouter<post::PostHandler,    data::Plan>               },
    {"problem",              &post::PostHandler::postSubrouter<post::PostHandler,    data::Problem>            },
    {"question",             &post::PostHandler::postSubrouter<post::PostHandler,    data::Question>           },
    {"role",                 &post::PostHandler::postSubrouter<post::PostHandler,    data::Role>               },
    {"safe_file",            &post::PostHandler::postSubrouter<post::PostHandler,    data::SafeFile>           },
    {"school",               &post::PostHandler::postSubrouter<post::PostHandler,    data::School>             },
    {"subject",              &post::PostHandler::postSubrouter<post::PostHandler,    data::Subject>            },
    {"submission",           &post::PostHandler::postSubrouter<post::PostHandler,    data::Submission>         },
    {"theme",                &post::PostHandler::postSubrouter<post::PostHandler,    data::Theme>              },
    {"user",                 &post::PostHandler::postSubrouter<post::UserHandler,    data::User>               }
};

std::unordered_map<std::string, decltype(&post::PostHandler::drop<data::Dummy>)> post::PostRouter::mDropRouter = {
    {"answer",               &post::PostHandler::drop<data::Answer>             },
    {"competition",          &post::PostHandler::drop<data::Competition>        },
    {"competition_problem",  &post::PostHandler::drop<data::CompetitionProblem> },
    {"competition_question", &post::PostHandler::drop<data::CompetitionQuestion>},
    {"competition_user",     &post::PostHandler::drop<data::CompetitionUser>    },
    {"dummy",                &post::PostHandler::drop<data::Dummy>              },
    {"file",                 &post::PostHandler::drop<data::File>               },
    {"file_exchange",        &post::PostHandler::drop<data::FileExchange>       },
    {"grade",                &post::PostHandler::drop<data::Grade>              },
    {"grade_student",        &post::PostHandler::drop<data::GradeStudent>       },
    {"group",                &post::PostHandler::drop<data::Group>              },
    {"group_student",        &post::PostHandler::drop<data::GroupStudent>       },
    {"holiday",              &post::PostHandler::drop<data::Holiday>            },
    {"journal_table",        &post::PostHandler::drop<data::JournalTable>       },
    {"lesson",               &post::PostHandler::drop<data::Lesson>             },
    {"mark",                 &post::PostHandler::drop<data::Mark>               },
    {"plan",                 &post::PostHandler::drop<data::Plan>               },
    {"problem",              &post::PostHandler::drop<data::Problem>            },
    {"question",             &post::PostHandler::drop<data::Question>           },
    {"role",                 &post::PostHandler::drop<data::Role>               },
    {"safe_file",            &post::PostHandler::drop<data::SafeFile>           },
    {"school",               &post::PostHandler::drop<data::School>             },
    {"subject",              &post::PostHandler::drop<data::Subject>            },
    {"submission",           &post::PostHandler::drop<data::Submission>         },
    {"theme",                &post::PostHandler::drop<data::Theme>              },
    {"user",                 &post::PostHandler::drop<data::User>               }
};

std::unordered_map<std::string, decltype(&post::PostHandler::rawDataHandler<data::Dummy>)> post::PostRouter::mRawDataRouter = {
    {"answer",               &post::PostHandler::rawDataHandler<data::Answer>             },
    {"competition",          &post::PostHandler::rawDataHandler<data::Competition>        },
    {"competition_problem",  &post::PostHandler::rawDataHandler<data::CompetitionProblem> },
    {"competition_question", &post::PostHandler::rawDataHandler<data::CompetitionQuestion>},
    {"competition_user",     &post::PostHandler::rawDataHandler<data::CompetitionUser>    },
    {"dummy",                &post::PostHandler::rawDataHandler<data::Dummy>              },
    {"file",                 &post::PostHandler::rawDataHandler<data::File>               },
    {"file_exchange",        &post::PostHandler::rawDataHandler<data::FileExchange>       },
    {"grade",                &post::PostHandler::rawDataHandler<data::Grade>              },
    {"grade_student",        &post::PostHandler::rawDataHandler<data::GradeStudent>       },
    {"group",                &post::PostHandler::rawDataHandler<data::Group>              },
    {"group_student",        &post::PostHandler::rawDataHandler<data::GroupStudent>       },
    {"holiday",              &post::PostHandler::rawDataHandler<data::Holiday>            },
    {"journal_table",        &post::JournalHandler::rawDataHandler                        },
    {"lesson",               &post::PostHandler::rawDataHandler<data::Lesson>             },
    {"mark",                 &post::PostHandler::rawDataHandler<data::Mark>               },
    {"plan",                 &post::PlanHandler::rawDataHandler                           },
    {"problem",              &post::PostHandler::rawDataHandler<data::Problem>            },
    {"question",             &post::PostHandler::rawDataHandler<data::Question>           },
    {"role",                 &post::PostHandler::rawDataHandler<data::Role>               },
    {"safe_file",            &post::PostHandler::rawDataHandler<data::SafeFile>           },
    {"school",               &post::PostHandler::rawDataHandler<data::School>             },
    {"subject",              &post::PostHandler::rawDataHandler<data::Subject>            },
    {"submission",           &post::PostHandler::rawDataHandler<data::Submission>         },
    {"theme",                &post::PostHandler::rawDataHandler<data::Theme>              },
    {"user",                 &post::UserHandler::rawDataHandler                           }
};
