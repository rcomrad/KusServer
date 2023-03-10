#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include "core/grade_handler.hpp"
#include "core/journal_handler.hpp"
#include "core/plan_handler.hpp"
#include "core/post_handler.hpp"

#define SERVER_FUNCTIONS                                                       \
    template <typename... Args>                                                \
    crow::json::wvalue::list getDataAsJSON(std::string_view aTableName,        \
                                           Args&&... args) noexcept            \
    {                                                                          \
        crow::json::wvalue::list res{400};                                     \
        auto hasher   = std::hash<std::string_view>{};                         \
        auto str_hash = hasher(aTableName);                                    \
                                                                               \
        if (str_hash == hasher("school"))                                      \
        {                                                                      \
            res = getData<data::School>(args...);                              \
        }                                                                      \
        else if (str_hash == hasher("user"))                                   \
        {                                                                      \
            res = getData<data::User>(args...);                                \
        }                                                                      \
        else if (str_hash == hasher("role"))                                   \
        {                                                                      \
            res = getData<data::Role>(args...);                                \
        }                                                                      \
        else if (str_hash == hasher("grade"))                                  \
        {                                                                      \
            res = getData<data::Grade>(args...);                               \
        }                                                                      \
        else if (str_hash == hasher("grade_student"))                          \
        {                                                                      \
            res = getData<data::Grade_student>(args...);                       \
        }                                                                      \
        else if (str_hash == hasher("group"))                                  \
        {                                                                      \
            res = getData<data::Group>(args...);                               \
        }                                                                      \
        else if (str_hash == hasher("group_student"))                          \
        {                                                                      \
            res = getData<data::Group_student>(args...);                       \
        }                                                                      \
        else if (str_hash == hasher("lesson"))                                 \
        {                                                                      \
            res = getData<data::Lesson>(args...);                              \
        }                                                                      \
        else if (str_hash == hasher("journal_table"))                          \
        {                                                                      \
            res = getData<data::Journal_table>(args...);                       \
        }                                                                      \
        else if (str_hash == hasher("subject"))                                \
        {                                                                      \
            res = getData<data::Subject>(args...);                             \
        }                                                                      \
        else if (str_hash == hasher("mark"))                                   \
        {                                                                      \
            res = getData<data::Mark>(args...);                                \
        }                                                                      \
        else if (str_hash == hasher("plan"))                                   \
        {                                                                      \
            res = getData<data::Plan>(args...);                                \
        }                                                                      \
        else if (str_hash == hasher("theme"))                                  \
        {                                                                      \
            res = getData<data::Theme>(args...);                               \
        }                                                                      \
        else if (str_hash == hasher("file"))                                   \
        {                                                                      \
            res = getData<data::File>(args...);                                \
        }                                                                      \
        else if (str_hash == hasher("holiday"))                                \
        {                                                                      \
            res = getData<data::Holiday>(args...);                             \
        }                                                                      \
        else if (str_hash == hasher("problem"))                                \
        {                                                                      \
            res = getData<data::Problem>(args...);                             \
        }                                                                      \
        else if (str_hash == hasher("submission"))                             \
        {                                                                      \
            res = getData<data::Submission>(args...);                          \
        }                                                                      \
        else if (str_hash == hasher("user_upload"))                            \
        {                                                                      \
            res = getData<data::User_upload>(args...);                         \
        }                                                                      \
        else if (str_hash == hasher("plan_upload"))                            \
        {                                                                      \
            res = getData<data::Plan_upload>(args...);                         \
        }                                                                      \
        else if (str_hash == hasher("journal_upload"))                         \
        {                                                                      \
            res = getData<data::Journal_upload>(args...);                      \
        }                                                                      \
        else if (str_hash == hasher("journal_download"))                       \
        {                                                                      \
            res = getData<data::Journal_download>(args...);                    \
        }                                                                      \
        else if (str_hash == hasher("question"))                               \
        {                                                                      \
            res = getData<data::Question>(args...);                            \
        }                                                                      \
        else if (str_hash == hasher("question_type"))                          \
        {                                                                      \
            res = getData<data::Question_type>(args...);                       \
        }                                                                      \
        else if (str_hash == hasher("question_answer"))                        \
        {                                                                      \
            res = getData<data::Question_answer>(args...);                     \
        }                                                                      \
        else if (str_hash == hasher("user_answer"))                            \
        {                                                                      \
            res = getData<data::User_answer>(args...);                         \
        }                                                                      \
                                                                               \
        return res;                                                            \
    }                                                                          \
                                                                               \
    template <typename... Args>                                                \
    crow::json::wvalue postRequestHandler(std::string_view aTableName,         \
                                          Args&&... args) noexcept             \
    {                                                                          \
        crow::json::wvalue res{400};                                           \
        auto hasher   = std::hash<std::string_view>{};                         \
        auto str_hash = hasher(aTableName);                                    \
                                                                               \
        if (str_hash == hasher("school"))                                      \
        {                                                                      \
            res = core::PostHandler::process<data::School>(args...);           \
        }                                                                      \
        else if (str_hash == hasher("user"))                                   \
        {                                                                      \
            res = core::PostHandler::process<data::User>(args...);             \
        }                                                                      \
        else if (str_hash == hasher("role"))                                   \
        {                                                                      \
            res = core::PostHandler::process<data::Role>(args...);             \
        }                                                                      \
        else if (str_hash == hasher("grade"))                                  \
        {                                                                      \
            res = core::PostHandler::process<data::Grade>(args...);            \
        }                                                                      \
        else if (str_hash == hasher("grade_student"))                          \
        {                                                                      \
            res = core::PostHandler::process<data::Grade_student>(args...);    \
        }                                                                      \
        else if (str_hash == hasher("group"))                                  \
        {                                                                      \
            res = core::PostHandler::process<data::Group>(args...);            \
        }                                                                      \
        else if (str_hash == hasher("group_student"))                          \
        {                                                                      \
            res = core::PostHandler::process<data::Group_student>(args...);    \
        }                                                                      \
        else if (str_hash == hasher("lesson"))                                 \
        {                                                                      \
            res = core::PostHandler::process<data::Lesson>(args...);           \
        }                                                                      \
        else if (str_hash == hasher("journal_table"))                          \
        {                                                                      \
            res = core::PostHandler::process<data::Journal_table>(args...);    \
        }                                                                      \
        else if (str_hash == hasher("subject"))                                \
        {                                                                      \
            res = core::PostHandler::process<data::Subject>(args...);          \
        }                                                                      \
        else if (str_hash == hasher("mark"))                                   \
        {                                                                      \
            res = core::PostHandler::process<data::Mark>(args...);             \
        }                                                                      \
        else if (str_hash == hasher("plan"))                                   \
        {                                                                      \
            res = core::PostHandler::process<data::Plan>(args...);             \
        }                                                                      \
        else if (str_hash == hasher("theme"))                                  \
        {                                                                      \
            res = core::PostHandler::process<data::Theme>(args...);            \
        }                                                                      \
        else if (str_hash == hasher("file"))                                   \
        {                                                                      \
            res = core::PostHandler::process<data::File>(args...);             \
        }                                                                      \
        else if (str_hash == hasher("holiday"))                                \
        {                                                                      \
            res = core::PostHandler::process<data::Holiday>(args...);          \
        }                                                                      \
        else if (str_hash == hasher("problem"))                                \
        {                                                                      \
            res = core::PostHandler::process<data::Problem>(args...);          \
        }                                                                      \
        else if (str_hash == hasher("submission"))                             \
        {                                                                      \
            res = core::PostHandler::process<data::Submission>(args...);       \
        }                                                                      \
        else if (str_hash == hasher("user_upload"))                            \
        {                                                                      \
            res = core::PostHandler::process<data::User_upload>(args...);      \
        }                                                                      \
        else if (str_hash == hasher("plan_upload"))                            \
        {                                                                      \
            res = core::PostHandler::process<data::Plan_upload>(args...);      \
        }                                                                      \
        else if (str_hash == hasher("journal_upload"))                         \
        {                                                                      \
            res = core::PostHandler::process<data::Journal_upload>(args...);   \
        }                                                                      \
        else if (str_hash == hasher("journal_download"))                       \
        {                                                                      \
            res = core::PostHandler::process<data::Journal_download>(args...); \
        }                                                                      \
        else if (str_hash == hasher("question"))                               \
        {                                                                      \
            res = core::PostHandler::process<data::Question>(args...);         \
        }                                                                      \
        else if (str_hash == hasher("question_type"))                          \
        {                                                                      \
            res = core::PostHandler::process<data::Question_type>(args...);    \
        }                                                                      \
        else if (str_hash == hasher("question_answer"))                        \
        {                                                                      \
            res = core::PostHandler::process<data::Question_answer>(args...);  \
        }                                                                      \
        else if (str_hash == hasher("user_answer"))                            \
        {                                                                      \
            res = core::PostHandler::process<data::User_answer>(args...);      \
        }                                                                      \
                                                                               \
        return res;                                                            \
    }                                                                          \
                                                                               \
    template <typename... Args>                                                \
    crow::json::wvalue dropRequestHandler(std::string_view aTableName,         \
                                          Args&&... args) noexcept             \
    {                                                                          \
        crow::json::wvalue res{400};                                           \
        auto hasher   = std::hash<std::string_view>{};                         \
        auto str_hash = hasher(aTableName);                                    \
                                                                               \
        if (str_hash == hasher("school"))                                      \
        {                                                                      \
            res = core::PostHandler::drop<data::School>(args...);              \
        }                                                                      \
        else if (str_hash == hasher("user"))                                   \
        {                                                                      \
            res = core::PostHandler::drop<data::User>(args...);                \
        }                                                                      \
        else if (str_hash == hasher("role"))                                   \
        {                                                                      \
            res = core::PostHandler::drop<data::Role>(args...);                \
        }                                                                      \
        else if (str_hash == hasher("grade"))                                  \
        {                                                                      \
            res = core::PostHandler::drop<data::Grade>(args...);               \
        }                                                                      \
        else if (str_hash == hasher("grade_student"))                          \
        {                                                                      \
            res = core::PostHandler::drop<data::Grade_student>(args...);       \
        }                                                                      \
        else if (str_hash == hasher("group"))                                  \
        {                                                                      \
            res = core::PostHandler::drop<data::Group>(args...);               \
        }                                                                      \
        else if (str_hash == hasher("group_student"))                          \
        {                                                                      \
            res = core::PostHandler::drop<data::Group_student>(args...);       \
        }                                                                      \
        else if (str_hash == hasher("lesson"))                                 \
        {                                                                      \
            res = core::PostHandler::drop<data::Lesson>(args...);              \
        }                                                                      \
        else if (str_hash == hasher("journal_table"))                          \
        {                                                                      \
            res = core::PostHandler::drop<data::Journal_table>(args...);       \
        }                                                                      \
        else if (str_hash == hasher("subject"))                                \
        {                                                                      \
            res = core::PostHandler::drop<data::Subject>(args...);             \
        }                                                                      \
        else if (str_hash == hasher("mark"))                                   \
        {                                                                      \
            res = core::PostHandler::drop<data::Mark>(args...);                \
        }                                                                      \
        else if (str_hash == hasher("plan"))                                   \
        {                                                                      \
            res = core::PostHandler::drop<data::Plan>(args...);                \
        }                                                                      \
        else if (str_hash == hasher("theme"))                                  \
        {                                                                      \
            res = core::PostHandler::drop<data::Theme>(args...);               \
        }                                                                      \
        else if (str_hash == hasher("file"))                                   \
        {                                                                      \
            res = core::PostHandler::drop<data::File>(args...);                \
        }                                                                      \
        else if (str_hash == hasher("holiday"))                                \
        {                                                                      \
            res = core::PostHandler::drop<data::Holiday>(args...);             \
        }                                                                      \
        else if (str_hash == hasher("problem"))                                \
        {                                                                      \
            res = core::PostHandler::drop<data::Problem>(args...);             \
        }                                                                      \
        else if (str_hash == hasher("submission"))                             \
        {                                                                      \
            res = core::PostHandler::drop<data::Submission>(args...);          \
        }                                                                      \
        else if (str_hash == hasher("user_upload"))                            \
        {                                                                      \
            res = core::PostHandler::drop<data::User_upload>(args...);         \
        }                                                                      \
        else if (str_hash == hasher("plan_upload"))                            \
        {                                                                      \
            res = core::PostHandler::drop<data::Plan_upload>(args...);         \
        }                                                                      \
        else if (str_hash == hasher("journal_upload"))                         \
        {                                                                      \
            res = core::PostHandler::drop<data::Journal_upload>(args...);      \
        }                                                                      \
        else if (str_hash == hasher("journal_download"))                       \
        {                                                                      \
            res = core::PostHandler::drop<data::Journal_download>(args...);    \
        }                                                                      \
        else if (str_hash == hasher("question"))                               \
        {                                                                      \
            res = core::PostHandler::drop<data::Question>(args...);            \
        }                                                                      \
        else if (str_hash == hasher("question_type"))                          \
        {                                                                      \
            res = core::PostHandler::drop<data::Question_type>(args...);       \
        }                                                                      \
        else if (str_hash == hasher("question_answer"))                        \
        {                                                                      \
            res = core::PostHandler::drop<data::Question_answer>(args...);     \
        }                                                                      \
        else if (str_hash == hasher("user_answer"))                            \
        {                                                                      \
            res = core::PostHandler::drop<data::User_answer>(args...);         \
        }                                                                      \
                                                                               \
        return res;                                                            \
    }

#endif // !REQUEST_HANDLER_HPP
