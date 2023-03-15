#include "post_routerrr.hpp"

std::unordered_map<std::string,
                   decltype(&post::PostHandler::process<data::User>)>
    post::PostRouterrr::mPostRouterMap = {
        {school,           &post::PostHandler::process<data::School>          },
        {user,             &post::UserHandler::process                        },
        {role,             &post::PostHandler::process<data::Role>            },
        {grade,            &post::PostHandler::process<data::Grade>           },
        {grade_student,    &post::PostHandler::process<data::Grade_student>   },
        {group,            &post::PostHandler::process<data::Group>           },
        {group_student,    &post::PostHandler::process<data::Group_student>   },
        {lesson,           &post::PostHandler::process<data::Lesson>          },
        {journal_table,    &post::JournalHandler::process                     },
        {subject,          &post::PostHandler::process<data::Subject>         },
        {mark,             &post::MarkHandler::process                        },
        {plan,             &post::PostHandler::process<data::Plan>            },
        {theme,            &post::PostHandler::process<data::Theme>           },
        {file,             &post::PostHandler::process<data::File>            },
        {holiday,          &post::PostHandler::process<data::Holiday>         },
        {problem,          &post::PostHandler::process<data::Problem>         },
        {submission,       &post::PostHandler::process<data::Submission>      },
        {user_upload,      &post::PostHandler::process<data::User_upload>     },
        {plan_upload,      &post::PostHandler::process<data::Plan_upload>     },
        {journal_upload,   &post::PostHandler::process<data::Journal_upload>  },
        {journal_download, &post::PostHandler::process<data::Journal_download>},
        {question,         &post::PostHandler::process<data::Question>        },
        {question_type,    &post::PostHandler::process<data::Question_type>   },
        {user_answer,      &post::UserAnswerHandler::process                  }
};

std::unordered_map<std::string,
                   decltype(&post::PostHandler::manyToMany<data::User>)>
    post::PostRouterrr::mManyToManyRouterMap = {
        {school,           &post::PostHandler::manyToMany<data::School>        },
        {user,             &post::PostHandler::manyToMany<data::User>          },
        {role,             &post::PostHandler::manyToMany<data::Role>          },
        {grade,            &post::PostHandler::manyToMany<data::Grade>         },
        {grade_student,    &post::PostHandler::manyToMany<data::Grade_student> },
        {group,            &post::PostHandler::manyToMany<data::Group>         },
        {group_student,    &post::PostHandler::manyToMany<data::Group_student> },
        {lesson,           &post::PostHandler::manyToMany<data::Lesson>        },
        {journal_table,    &post::PostHandler::manyToMany<data::Journal_table> },
        {subject,          &post::PostHandler::manyToMany<data::Subject>       },
        {mark,             &post::PostHandler::manyToMany<data::Mark>          },
        {plan,             &post::PostHandler::manyToMany<data::Plan>          },
        {theme,            &post::PostHandler::manyToMany<data::Theme>         },
        {file,             &post::PostHandler::manyToMany<data::File>          },
        {holiday,          &post::PostHandler::manyToMany<data::Holiday>       },
        {problem,          &post::PostHandler::manyToMany<data::Problem>       },
        {submission,       &post::PostHandler::manyToMany<data::Submission>    },
        {user_upload,      &post::PostHandler::manyToMany<data::User_upload>   },
        {plan_upload,      &post::PostHandler::manyToMany<data::Plan_upload>   },
        {journal_upload,   &post::PostHandler::manyToMany<data::Journal_upload>},
        {journal_download,
         &post::PostHandler::manyToMany<data::Journal_download>                },
        {question,         &post::PostHandler::manyToMany<data::Question>      },
        {question_type,    &post::PostHandler::manyToMany<data::Question_type> },
        {user_answer,      &post::PostHandler::manyToMany<data::User_answer>   }
};

std::unordered_map<std::string,
                   decltype(&post::PostHandler::uploadFromFile<data::User>)>
    post::PostRouterrr::mUploadRouterMap = {
        {school,           &post::PostHandler::uploadFromFile<data::School>     },
        {user,             &post::UserHandler::uploadFromFile                   },
        {role,             &post::PostHandler::uploadFromFile<data::Role>       },
        {grade,            &post::PostHandler::uploadFromFile<data::Grade>      },
        {grade_student,
         &post::PostHandler::uploadFromFile<data::Grade_student>                },
        {group,            &post::PostHandler::uploadFromFile<data::Group>      },
        {group_student,
         &post::PostHandler::uploadFromFile<data::Group_student>                },
        {lesson,           &post::PostHandler::uploadFromFile<data::Lesson>     },
        {journal_table,    &post::JournalHandler::uploadFromFile                },
        {subject,          &post::PostHandler::uploadFromFile<data::Subject>    },
        {mark,             &post::PostHandler::uploadFromFile<data::Mark>       },
        {plan,             &post::PlanHandler::uploadFromFile                   },
        {theme,            &post::PostHandler::uploadFromFile<data::Theme>      },
        {file,             &post::PostHandler::uploadFromFile<data::File>       },
        {holiday,          &post::PostHandler::uploadFromFile<data::Holiday>    },
        {problem,          &post::PostHandler::uploadFromFile<data::Problem>    },
        {submission,       &post::PostHandler::uploadFromFile<data::Submission> },
        {user_upload,      &post::PostHandler::uploadFromFile<data::User_upload>},
        {plan_upload,      &post::PostHandler::uploadFromFile<data::Plan_upload>},
        {journal_upload,
         &post::PostHandler::uploadFromFile<data::Journal_upload>               },
        {journal_download,
         &post::PostHandler::uploadFromFile<data::Journal_download>             },
        {question,         &post::PostHandler::uploadFromFile<data::Question>   },
        {question_type,
         &post::PostHandler::uploadFromFile<data::Question_type>                },
        {user_answer,      &post::PostHandler::uploadFromFile<data::User_answer>}
};

std::unordered_map<std::string, decltype(&post::PostHandler::drop<data::User>)>
    post::PostRouterrr::mDropRouterMap = {
        {school,           &post::PostHandler::drop<data::School>          },
        {user,             &post::PostHandler::drop<data::User>            },
        {role,             &post::PostHandler::drop<data::Role>            },
        {grade,            &post::PostHandler::drop<data::Grade>           },
        {grade_student,    &post::PostHandler::drop<data::Grade_student>   },
        {group,            &post::PostHandler::drop<data::Group>           },
        {group_student,    &post::PostHandler::drop<data::Group_student>   },
        {lesson,           &post::PostHandler::drop<data::Lesson>          },
        {journal_table,    &post::PostHandler::drop<data::Journal_table>   },
        {subject,          &post::PostHandler::drop<data::Subject>         },
        {mark,             &post::PostHandler::drop<data::Mark>            },
        {plan,             &post::PostHandler::drop<data::Plan>            },
        {theme,            &post::PostHandler::drop<data::Theme>           },
        {file,             &post::PostHandler::drop<data::File>            },
        {holiday,          &post::PostHandler::drop<data::Holiday>         },
        {problem,          &post::PostHandler::drop<data::Problem>         },
        {submission,       &post::PostHandler::drop<data::Submission>      },
        {user_upload,      &post::PostHandler::drop<data::User_upload>     },
        {plan_upload,      &post::PostHandler::drop<data::Plan_upload>     },
        {journal_upload,   &post::PostHandler::drop<data::Journal_upload>  },
        {journal_download, &post::PostHandler::drop<data::Journal_download>},
        {question,         &post::PostHandler::drop<data::Question>        },
        {question_type,    &post::PostHandler::drop<data::Question_type>   },
        {user_answer,      &post::PostHandler::drop<data::User_answer>     }
};
