#include "get_router.hpp"

#include "question_handler.hpp"
#include "user_handler.hpp"

std::unordered_map<std::string, decltype(&get::GetHandler::process<data::User>)>
    get::GetRouter::mBasicRouterMap = {
        {"school",               &get::GetHandler::process<data::School>          },
        {"user",                 &get::UserHandler::process                       },
        {"role",                 &get::GetHandler::process<data::Role>            },
        {"grade",                &get::GetHandler::process<data::Grade>           },
        {"grade_student",        &get::GetHandler::process<data::Grade_student>   },
        {"group",                &get::GetHandler::process<data::Group>           },
        {"group_student",        &get::GetHandler::process<data::Group_student>   },
        {"lesson",               &get::GetHandler::process<data::Lesson>          },
        {"journal_table",        &get::GetHandler::process<data::Journal_table>   },
        {"subject",              &get::GetHandler::process<data::Subject>         },
        {"mark",                 &get::GetHandler::process<data::Mark>            },
        {"plan",                 &get::GetHandler::process<data::Plan>            },
        {"theme",                &get::GetHandler::process<data::Theme>           },
        {"file",                 &get::GetHandler::process<data::File>            },
        {"safe_file",            &get::GetHandler::process<data::Safe_file>       },
        {"holiday",              &get::GetHandler::process<data::Holiday>         },
        {"competition",          &get::GetHandler::process<data::Competition>     },
        {"user_competition",     &get::GetHandler::process<data::User_competition>},
        {"problem",              &get::GetHandler::process<data::Problem>         },
        {"competition_problem",
         &get::GetHandler::process<data::Competition_problem>                     },
        {"submission",           &get::GetHandler::process<data::Submission>      },
        {"question",             &get::GetHandler::process<data::Question>        },
        {"competition_question",
         &get::GetHandler::process<data::Competition_question>                    },
        {"answer",               &get::GetHandler::process<data::Answer>          },
        {"file_exchange",        &get::GetHandler::process<data::File_exchange>   }
};

std::unordered_map<std::string, decltype(&get::GetHandler::dump<data::User>)>
    get::GetRouter::mDumpRouterMap = {
        {"school",               &get::GetHandler::dump<data::School>          },
        {"user",                 &get::GetHandler::dump<data::User>            },
        {"role",                 &get::GetHandler::dump<data::Role>            },
        {"grade",                &get::GetHandler::dump<data::Grade>           },
        {"grade_student",        &get::GetHandler::dump<data::Grade_student>   },
        {"group",                &get::GetHandler::dump<data::Group>           },
        {"group_student",        &get::GetHandler::dump<data::Group_student>   },
        {"lesson",               &get::GetHandler::dump<data::Lesson>          },
        {"journal_table",        &get::GetHandler::dump<data::Journal_table>   },
        {"subject",              &get::GetHandler::dump<data::Subject>         },
        {"mark",                 &get::GetHandler::dump<data::Mark>            },
        {"plan",                 &get::GetHandler::dump<data::Plan>            },
        {"theme",                &get::GetHandler::dump<data::Theme>           },
        {"file",                 &get::GetHandler::dump<data::File>            },
        {"safe_file",            &get::GetHandler::dump<data::Safe_file>       },
        {"holiday",              &get::GetHandler::dump<data::Holiday>         },
        {"competition",          &get::GetHandler::dump<data::Competition>     },
        {"user_competition",     &get::GetHandler::dump<data::User_competition>},
        {"problem",              &get::GetHandler::dump<data::Problem>         },
        {"competition_problem",
         &get::GetHandler::dump<data::Competition_problem>                     },
        {"submission",           &get::GetHandler::dump<data::Submission>      },
        {"question",             &get::GetHandler::dump<data::Question>        },
        {"competition_question",
         &get::GetHandler::dump<data::Competition_question>                    },
        {"answer",               &get::GetHandler::dump<data::Answer>          },
        {"file_exchange",        &get::GetHandler::dump<data::File_exchange>   }
};
