#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include "core/grade_handler.hpp"
#include "core/journal_handler.hpp"
#include "core/plan_handler.hpp"
#include "core/post_handler.hpp"

#define SERVER_FUNCTIONS                                                    \
    template <typename... Args>                                             \
    crow::json::wvalue::list getDataAsJSON(std::string_view aTableName,     \
                                           Args&&... args) noexcept         \
    {                                                                       \
        crow::json::wvalue::list res{400};                                  \
        auto hasher   = std::hash<std::string_view>{};                      \
        auto str_hash = hasher(aTableName);                                 \
                                                                            \
        if (str_hash == hasher("school"))                                   \
        {                                                                   \
            res = getData<data::School>(args...);                           \
        }                                                                   \
        else if (str_hash == hasher("user"))                                \
        {                                                                   \
            res = getData<data::User>(args...);                             \
        }                                                                   \
        else if (str_hash == hasher("role"))                                \
        {                                                                   \
            res = getData<data::Role>(args...);                             \
        }                                                                   \
        else if (str_hash == hasher("grade"))                               \
        {                                                                   \
            res = getData<data::Grade>(args...);                            \
        }                                                                   \
        else if (str_hash == hasher("grade_student"))                       \
        {                                                                   \
            res = getData<data::Grade_student>(args...);                    \
        }                                                                   \
        else if (str_hash == hasher("group"))                               \
        {                                                                   \
            res = getData<data::Group>(args...);                            \
        }                                                                   \
        else if (str_hash == hasher("group_student"))                       \
        {                                                                   \
            res = getData<data::Group_student>(args...);                    \
        }                                                                   \
        else if (str_hash == hasher("lesson"))                              \
        {                                                                   \
            res = getData<data::Lesson>(args...);                           \
        }                                                                   \
        else if (str_hash == hasher("journal_table"))                       \
        {                                                                   \
            res = getData<data::Journal_table>(args...);                    \
        }                                                                   \
        else if (str_hash == hasher("subject"))                             \
        {                                                                   \
            res = getData<data::Subject>(args...);                          \
        }                                                                   \
        else if (str_hash == hasher("mark"))                                \
        {                                                                   \
            res = getData<data::Mark>(args...);                             \
        }                                                                   \
        else if (str_hash == hasher("plan"))                                \
        {                                                                   \
            res = getData<data::Plan>(args...);                             \
        }                                                                   \
        else if (str_hash == hasher("theme"))                               \
        {                                                                   \
            res = getData<data::Theme>(args...);                            \
        }                                                                   \
        else if (str_hash == hasher("file"))                                \
        {                                                                   \
            res = getData<data::File>(args...);                             \
        }                                                                   \
        else if (str_hash == hasher("holiday"))                             \
        {                                                                   \
            res = getData<data::Holiday>(args...);                          \
        }                                                                   \
        else if (str_hash == hasher("problem"))                             \
        {                                                                   \
            res = getData<data::Problem>(args...);                          \
        }                                                                   \
        else if (str_hash == hasher("submission"))                          \
        {                                                                   \
            res = getData<data::Submission>(args...);                       \
        }                                                                   \
                                                                            \
        return res;                                                         \
    }                                                                       \
                                                                            \
    template <typename... Args>                                             \
    crow::json::wvalue postRequestHandler(std::string_view aTableName,      \
                                          Args&&... args) noexcept          \
    {                                                                       \
        crow::json::wvalue res{400};                                        \
        auto hasher   = std::hash<std::string_view>{};                      \
        auto str_hash = hasher(aTableName);                                 \
                                                                            \
        if (str_hash == hasher("school"))                                   \
        {                                                                   \
            res = core::PostHandler::process<data::School>(args...);        \
        }                                                                   \
        else if (str_hash == hasher("user"))                                \
        {                                                                   \
            res = core::PostHandler::process<data::User>(args...);          \
        }                                                                   \
        else if (str_hash == hasher("role"))                                \
        {                                                                   \
            res = core::PostHandler::process<data::Role>(args...);          \
        }                                                                   \
        else if (str_hash == hasher("grade"))                               \
        {                                                                   \
            res = core::PostHandler::process<data::Grade>(args...);         \
        }                                                                   \
        else if (str_hash == hasher("grade_student"))                       \
        {                                                                   \
            res = core::PostHandler::process<data::Grade_student>(args...); \
        }                                                                   \
        else if (str_hash == hasher("group"))                               \
        {                                                                   \
            res = core::PostHandler::process<data::Group>(args...);         \
        }                                                                   \
        else if (str_hash == hasher("group_student"))                       \
        {                                                                   \
            res = core::PostHandler::process<data::Group_student>(args...); \
        }                                                                   \
        else if (str_hash == hasher("lesson"))                              \
        {                                                                   \
            res = core::PostHandler::process<data::Lesson>(args...);        \
        }                                                                   \
        else if (str_hash == hasher("journal_table"))                       \
        {                                                                   \
            res = core::PostHandler::process<data::Journal_table>(args...); \
        }                                                                   \
        else if (str_hash == hasher("subject"))                             \
        {                                                                   \
            res = core::PostHandler::process<data::Subject>(args...);       \
        }                                                                   \
        else if (str_hash == hasher("mark"))                                \
        {                                                                   \
            res = core::PostHandler::process<data::Mark>(args...);          \
        }                                                                   \
        else if (str_hash == hasher("plan"))                                \
        {                                                                   \
            res = core::PostHandler::process<data::Plan>(args...);          \
        }                                                                   \
        else if (str_hash == hasher("theme"))                               \
        {                                                                   \
            res = core::PostHandler::process<data::Theme>(args...);         \
        }                                                                   \
        else if (str_hash == hasher("file"))                                \
        {                                                                   \
            res = core::PostHandler::process<data::File>(args...);          \
        }                                                                   \
        else if (str_hash == hasher("holiday"))                             \
        {                                                                   \
            res = core::PostHandler::process<data::Holiday>(args...);       \
        }                                                                   \
        else if (str_hash == hasher("problem"))                             \
        {                                                                   \
            res = core::PostHandler::process<data::Problem>(args...);       \
        }                                                                   \
        else if (str_hash == hasher("submission"))                          \
        {                                                                   \
            res = core::PostHandler::process<data::Submission>(args...);    \
        }                                                                   \
                                                                            \
        return res;                                                         \
    }
#endif // !REQUEST_HANDLER_HPP
