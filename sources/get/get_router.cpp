#include "get_router.hpp"

std::unordered_map<std::string, decltype(&get::GetHandler::process<data::User>)>
    get::GetRouter::mBasicRouterMap = {
        {"school",           &get::GetHandler::process<data::School>          },
        {"user",             &get::UserHandler::process                       },
        {"role",             &get::GetHandler::process<data::Role>            },
        {"grade",            &get::GetHandler::process<data::Grade>           },
        {"grade_student",    &get::GetHandler::process<data::Grade_student>   },
        {"group",            &get::GetHandler::process<data::Group>           },
        {"group_student",    &get::GetHandler::process<data::Group_student>   },
        {"lesson",           &get::GetHandler::process<data::Lesson>          },
        {"journal_table",    &get::GetHandler::process<data::Journal_table>   },
        {"subject",          &get::GetHandler::process<data::Subject>         },
        {"mark",             &get::GetHandler::process<data::Mark>            },
        {"plan",             &get::GetHandler::process<data::Plan>            },
        {"theme",            &get::GetHandler::process<data::Theme>           },
        {"file",             &get::GetHandler::process<data::File>            },
        {"holiday",          &get::GetHandler::process<data::Holiday>         },
        {"problem",          &get::GetHandler::process<data::Problem>         },
        {"submission",       &get::GetHandler::process<data::Submission>      },
        {"user_upload",      &get::GetHandler::process<data::User_upload>     },
        {"plan_upload",      &get::GetHandler::process<data::Plan_upload>     },
        {"journal_upload",   &get::GetHandler::process<data::Journal_upload>  },
        {"journal_download", &get::GetHandler::process<data::Journal_download>},
        {"question",         &get::GetHandler::process<data::Question>        },
        {"question_type",    &get::GetHandler::process<data::Question_type>   },
        {"user_answer",      &get::GetHandler::process<data::User_answer>     }
};
