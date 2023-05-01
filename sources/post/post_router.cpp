#include "post_router.hpp"

#include "answer_handler.hpp"
#include "journal_handler.hpp"
#include "mark_handler.hpp"
#include "plan_handler.hpp"
#include "user_handler.hpp"

std::unordered_map<std::string,
                   decltype(&post::PostHandler::process<data::Dummy>)>
    post::PostRouter::mPostRouterMap = {
        {"dummy",                &post::PostHandler::process<data::Dummy>        },
        {"school",               &post::PostHandler::process<data::School>       },
        {"user",                 &post::UserHandler::process                     },
        {"role",                 &post::PostHandler::process<data::Role>         },
        {"grade",                &post::PostHandler::process<data::Grade>        },
        {"grade_student",        &post::PostHandler::process<data::Grade_student>},
        {"group",                &post::PostHandler::process<data::Group>        },
        {"group_student",        &post::PostHandler::process<data::Group_student>},
        {"lesson",               &post::PostHandler::process<data::Lesson>       },
        {"journal_table",        &post::JournalHandler::process                  },
        {"subject",              &post::PostHandler::process<data::Subject>      },
        {"mark",                 &post::MarkHandler::process                     },
        {"plan",                 &post::PostHandler::process<data::Plan>         },
        {"theme",                &post::PostHandler::process<data::Theme>        },
        {"file",                 &post::PostHandler::process<data::File>         },
        {"safe_file",            &post::PostHandler::process<data::Safe_file>    },
        {"holiday",              &post::PostHandler::process<data::Holiday>      },
        {"competition",          &post::PostHandler::process<data::Competition>  },
        {"user_competition",
         &post::PostHandler::process<data::User_competition>                     },
        {"problem",              &post::PostHandler::process<data::Problem>      },
        {"competition_problem",
         &post::PostHandler::process<data::Competition_problem>                  },
        {"submission",           &post::PostHandler::process<data::Submission>   },
        {"question",             &post::PostHandler::process<data::Question>     },
        {"competition_question",
         &post::PostHandler::process<data::Competition_question>                 },
        {"answer",               &post::AnswerHandler::process                   },
        {"file_exchange",        &post::PostHandler::process<data::File_exchange>}
};

std::unordered_map<std::string, decltype(&post::PostHandler::drop<data::Dummy>)>
    post::PostRouter::mDropRouterMap = {
        {"dummy",                &post::PostHandler::drop<data::Dummy>           },
        {"school",               &post::PostHandler::drop<data::School>          },
        {"user",                 &post::PostHandler::drop<data::User>            },
        {"role",                 &post::PostHandler::drop<data::Role>            },
        {"grade",                &post::PostHandler::drop<data::Grade>           },
        {"grade_student",        &post::PostHandler::drop<data::Grade_student>   },
        {"group",                &post::PostHandler::drop<data::Group>           },
        {"group_student",        &post::PostHandler::drop<data::Group_student>   },
        {"lesson",               &post::PostHandler::drop<data::Lesson>          },
        {"journal_table",        &post::PostHandler::drop<data::Journal_table>   },
        {"subject",              &post::PostHandler::drop<data::Subject>         },
        {"mark",                 &post::PostHandler::drop<data::Mark>            },
        {"plan",                 &post::PostHandler::drop<data::Plan>            },
        {"theme",                &post::PostHandler::drop<data::Theme>           },
        {"file",                 &post::PostHandler::drop<data::File>            },
        {"safe_file",            &post::PostHandler::drop<data::Safe_file>       },
        {"holiday",              &post::PostHandler::drop<data::Holiday>         },
        {"competition",          &post::PostHandler::drop<data::Competition>     },
        {"user_competition",     &post::PostHandler::drop<data::User_competition>},
        {"problem",              &post::PostHandler::drop<data::Problem>         },
        {"competition_problem",
         &post::PostHandler::drop<data::Competition_problem>                     },
        {"submission",           &post::PostHandler::drop<data::Submission>      },
        {"question",             &post::PostHandler::drop<data::Question>        },
        {"competition_question",
         &post::PostHandler::drop<data::Competition_question>                    },
        {"answer",               &post::PostHandler::drop<data::Answer>          },
        {"file_exchange",        &post::PostHandler::drop<data::File_exchange>   }
};

std::unordered_map<std::string,
                   decltype(&post::PostHandler::rawDataHandler<data::Dummy>)>
    post::PostRouter::mRawDataRouter = {
        {"dummy",                &post::PostHandler::rawDataHandler<data::Dummy>      },
        {"school",               &post::PostHandler::rawDataHandler<data::School>     },
        {"user",                 &post::UserHandler::rawDataHandler                   },
        {"role",                 &post::PostHandler::rawDataHandler<data::Role>       },
        {"grade",                &post::PostHandler::rawDataHandler<data::Grade>      },
        {"grade_student",
         &post::PostHandler::rawDataHandler<data::Grade_student>                      },
        {"group",                &post::PostHandler::rawDataHandler<data::Group>      },
        {"group_student",
         &post::PostHandler::rawDataHandler<data::Group_student>                      },
        {"lesson",               &post::PostHandler::rawDataHandler<data::Lesson>     },
        {"journal_table",        &post::JournalHandler::rawDataHandler                },
        {"subject",              &post::PostHandler::rawDataHandler<data::Subject>    },
        {"mark",                 &post::PostHandler::rawDataHandler<data::Mark>       },
        {"plan",                 &post::PlanHandler::rawDataHandler                   },
        {"theme",                &post::PostHandler::rawDataHandler<data::Theme>      },
        {"file",                 &post::PostHandler::rawDataHandler<data::File>       },
        {"safe_file",            &post::PostHandler::rawDataHandler<data::Safe_file>  },
        {"holiday",              &post::PostHandler::rawDataHandler<data::Holiday>    },
        {"competition",          &post::PostHandler::rawDataHandler<data::Competition>},
        {"user_competition",
         &post::PostHandler::rawDataHandler<data::User_competition>                   },
        {"problem",              &post::PostHandler::rawDataHandler<data::Problem>    },
        {"competition_problem",
         &post::PostHandler::rawDataHandler<data::Competition_problem>                },
        {"submission",           &post::PostHandler::rawDataHandler<data::Submission> },
        {"question",             &post::PostHandler::rawDataHandler<data::Question>   },
        {"competition_question",
         &post::PostHandler::rawDataHandler<data::Competition_question>               },
        {"answer",               &post::PostHandler::rawDataHandler<data::Answer>     },
        {"file_exchange",
         &post::PostHandler::rawDataHandler<data::File_exchange>                      }
};
