#ifndef POST_ROUTER_HPP
#define POST_ROUTER_HPP

#include "journal_handler.hpp"
#include "mark_handler.hpp"
#include "plan_handler.hpp"
#include "post_handler.hpp"
#include "user_answer_handler.hpp"
#include "user_handler.hpp"

namespace post
{
class PostRouter
{
public:
    template <typename... Args>
    static crow::json::wvalue basicRouter(std::string_view aTableName,
                                          Args&&... args) noexcept
    {
        crow::json::wvalue res{400};
        auto hasher   = std::hash<std::string_view>{};
        auto str_hash = hasher(aTableName);

        if (str_hash == hasher("school"))
        {
            res = post::PostHandler::process<data::School>(args...);
        }
        else if (str_hash == hasher("user"))
        {
            res = post::UserHandler::process(args...);
        }
        else if (str_hash == hasher("role"))
        {
            res = post::PostHandler::process<data::Role>(args...);
        }
        else if (str_hash == hasher("grade"))
        {
            res = post::PostHandler::process<data::Grade>(args...);
        }
        else if (str_hash == hasher("grade_student"))
        {
            res = post::PostHandler::process<data::Grade_student>(args...);
        }
        else if (str_hash == hasher("group"))
        {
            res = post::PostHandler::process<data::Group>(args...);
        }
        else if (str_hash == hasher("group_student"))
        {
            res = post::PostHandler::process<data::Group_student>(args...);
        }
        else if (str_hash == hasher("lesson"))
        {
            res = post::PostHandler::process<data::Lesson>(args...);
        }
        else if (str_hash == hasher("journal_table"))
        {
            res = post::JournalHandler::process(args...);
        }
        else if (str_hash == hasher("subject"))
        {
            res = post::PostHandler::process<data::Subject>(args...);
        }
        else if (str_hash == hasher("mark"))
        {
            res = post::MarkHandler::process(args...);
        }
        else if (str_hash == hasher("plan"))
        {
            res = post::PostHandler::process<data::Plan>(args...);
        }
        else if (str_hash == hasher("theme"))
        {
            res = post::PostHandler::process<data::Theme>(args...);
        }
        else if (str_hash == hasher("file"))
        {
            res = post::PostHandler::process<data::File>(args...);
        }
        else if (str_hash == hasher("holiday"))
        {
            res = post::PostHandler::process<data::Holiday>(args...);
        }
        else if (str_hash == hasher("problem"))
        {
            res = post::PostHandler::process<data::Problem>(args...);
        }
        else if (str_hash == hasher("submission"))
        {
            res = post::PostHandler::process<data::Submission>(args...);
        }
        else if (str_hash == hasher("user_upload"))
        {
            res = post::PostHandler::process<data::User_upload>(args...);
        }
        else if (str_hash == hasher("plan_upload"))
        {
            res = post::PostHandler::process<data::Plan_upload>(args...);
        }
        else if (str_hash == hasher("journal_upload"))
        {
            res = post::PostHandler::process<data::Journal_upload>(args...);
        }
        else if (str_hash == hasher("journal_download"))
        {
            res = post::PostHandler::process<data::Journal_download>(args...);
        }
        else if (str_hash == hasher("question"))
        {
            res = post::PostHandler::process<data::Question>(args...);
        }
        else if (str_hash == hasher("question_type"))
        {
            res = post::PostHandler::process<data::Question_type>(args...);
        }
        else if (str_hash == hasher("user_answer"))
        {
            res = post::UserAnswerHandler::process(args...);
        }

        return res;
    }

    template <typename... Args>
    static crow::json::wvalue manyToManyRouter(std::string_view aTableName,
                                               Args&&... args) noexcept
    {
        crow::json::wvalue res{400};
        auto hasher   = std::hash<std::string_view>{};
        auto str_hash = hasher(aTableName);

        if (str_hash == hasher("school"))
        {
            res = post::PostHandler::manyToMany<data::School>(args...);
        }
        else if (str_hash == hasher("user"))
        {
            res = post::PostHandler::manyToMany<data::User>(args...);
        }
        else if (str_hash == hasher("role"))
        {
            res = post::PostHandler::manyToMany<data::Role>(args...);
        }
        else if (str_hash == hasher("grade"))
        {
            res = post::PostHandler::manyToMany<data::Grade>(args...);
        }
        else if (str_hash == hasher("grade_student"))
        {
            res = post::PostHandler::manyToMany<data::Grade_student>(args...);
        }
        else if (str_hash == hasher("group"))
        {
            res = post::PostHandler::manyToMany<data::Group>(args...);
        }
        else if (str_hash == hasher("group_student"))
        {
            res = post::PostHandler::manyToMany<data::Group_student>(args...);
        }
        else if (str_hash == hasher("lesson"))
        {
            res = post::PostHandler::manyToMany<data::Lesson>(args...);
        }
        else if (str_hash == hasher("journal_table"))
        {
            res = post::PostHandler::manyToMany<data::Journal_table>(args...);
        }
        else if (str_hash == hasher("subject"))
        {
            res = post::PostHandler::manyToMany<data::Subject>(args...);
        }
        else if (str_hash == hasher("mark"))
        {
            res = post::PostHandler::manyToMany<data::Mark>(args...);
        }
        else if (str_hash == hasher("plan"))
        {
            res = post::PostHandler::manyToMany<data::Plan>(args...);
        }
        else if (str_hash == hasher("theme"))
        {
            res = post::PostHandler::manyToMany<data::Theme>(args...);
        }
        else if (str_hash == hasher("file"))
        {
            res = post::PostHandler::manyToMany<data::File>(args...);
        }
        else if (str_hash == hasher("holiday"))
        {
            res = post::PostHandler::manyToMany<data::Holiday>(args...);
        }
        else if (str_hash == hasher("problem"))
        {
            res = post::PostHandler::manyToMany<data::Problem>(args...);
        }
        else if (str_hash == hasher("submission"))
        {
            res = post::PostHandler::manyToMany<data::Submission>(args...);
        }
        else if (str_hash == hasher("user_upload"))
        {
            res = post::PostHandler::manyToMany<data::User_upload>(args...);
        }
        else if (str_hash == hasher("plan_upload"))
        {
            res = post::PostHandler::manyToMany<data::Plan_upload>(args...);
        }
        else if (str_hash == hasher("journal_upload"))
        {
            res = post::PostHandler::manyToMany<data::Journal_upload>(args...);
        }
        else if (str_hash == hasher("journal_download"))
        {
            res =
                post::PostHandler::manyToMany<data::Journal_download>(args...);
        }
        else if (str_hash == hasher("question"))
        {
            res = post::PostHandler::manyToMany<data::Question>(args...);
        }
        else if (str_hash == hasher("question_type"))
        {
            res = post::PostHandler::manyToMany<data::Question_type>(args...);
        }
        else if (str_hash == hasher("user_answer"))
        {
            res = post::PostHandler::manyToMany<data::User_answer>(args...);
        }

        return res;
    }

    template <typename... Args>
    static crow::json::wvalue uploadRouter(std::string_view aTableName,
                                           Args&&... args) noexcept
    {
        crow::json::wvalue res{400};
        auto hasher   = std::hash<std::string_view>{};
        auto str_hash = hasher(aTableName);

        if (str_hash == hasher("school"))
        {
            res = post::PostHandler::uploadFromFile<data::School>(args...);
        }
        else if (str_hash == hasher("user"))
        {
            res = post::UserHandler::uploadFromFile(args...);
        }
        else if (str_hash == hasher("role"))
        {
            res = post::PostHandler::uploadFromFile<data::Role>(args...);
        }
        else if (str_hash == hasher("grade"))
        {
            res = post::PostHandler::uploadFromFile<data::Grade>(args...);
        }
        else if (str_hash == hasher("grade_student"))
        {
            res =
                post::PostHandler::uploadFromFile<data::Grade_student>(args...);
        }
        else if (str_hash == hasher("group"))
        {
            res = post::PostHandler::uploadFromFile<data::Group>(args...);
        }
        else if (str_hash == hasher("group_student"))
        {
            res =
                post::PostHandler::uploadFromFile<data::Group_student>(args...);
        }
        else if (str_hash == hasher("lesson"))
        {
            res = post::PostHandler::uploadFromFile<data::Lesson>(args...);
        }
        else if (str_hash == hasher("journal_table"))
        {
            res = post::JournalHandler::uploadFromFile(args...);
        }
        else if (str_hash == hasher("subject"))
        {
            res = post::PostHandler::uploadFromFile<data::Subject>(args...);
        }
        else if (str_hash == hasher("mark"))
        {
            res = post::PostHandler::uploadFromFile<data::Mark>(args...);
        }
        else if (str_hash == hasher("plan"))
        {
            res = post::PlanHandler::uploadFromFile(args...);
        }
        else if (str_hash == hasher("theme"))
        {
            res = post::PostHandler::uploadFromFile<data::Theme>(args...);
        }
        else if (str_hash == hasher("file"))
        {
            res = post::PostHandler::uploadFromFile<data::File>(args...);
        }
        else if (str_hash == hasher("holiday"))
        {
            res = post::PostHandler::uploadFromFile<data::Holiday>(args...);
        }
        else if (str_hash == hasher("problem"))
        {
            res = post::PostHandler::uploadFromFile<data::Problem>(args...);
        }
        else if (str_hash == hasher("submission"))
        {
            res = post::PostHandler::uploadFromFile<data::Submission>(args...);
        }
        else if (str_hash == hasher("user_upload"))
        {
            res = post::PostHandler::uploadFromFile<data::User_upload>(args...);
        }
        else if (str_hash == hasher("plan_upload"))
        {
            res = post::PostHandler::uploadFromFile<data::Plan_upload>(args...);
        }
        else if (str_hash == hasher("journal_upload"))
        {
            res = post::PostHandler::uploadFromFile<data::Journal_upload>(
                args...);
        }
        else if (str_hash == hasher("journal_download"))
        {
            res = post::PostHandler::uploadFromFile<data::Journal_download>(
                args...);
        }
        else if (str_hash == hasher("question"))
        {
            res = post::PostHandler::uploadFromFile<data::Question>(args...);
        }
        else if (str_hash == hasher("question_type"))
        {
            res =
                post::PostHandler::uploadFromFile<data::Question_type>(args...);
        }
        else if (str_hash == hasher("user_answer"))
        {
            res = post::PostHandler::uploadFromFile<data::User_answer>(args...);
        }

        return res;
    }

    template <typename... Args>
    static crow::json::wvalue dropRouter(std::string_view aTableName,
                                         Args&&... args) noexcept
    {
        crow::json::wvalue res{400};
        auto hasher   = std::hash<std::string_view>{};
        auto str_hash = hasher(aTableName);

        if (str_hash == hasher("school"))
        {
            res = post::PostHandler::drop<data::School>(args...);
        }
        else if (str_hash == hasher("user"))
        {
            res = post::PostHandler::drop<data::User>(args...);
        }
        else if (str_hash == hasher("role"))
        {
            res = post::PostHandler::drop<data::Role>(args...);
        }
        else if (str_hash == hasher("grade"))
        {
            res = post::PostHandler::drop<data::Grade>(args...);
        }
        else if (str_hash == hasher("grade_student"))
        {
            res = post::PostHandler::drop<data::Grade_student>(args...);
        }
        else if (str_hash == hasher("group"))
        {
            res = post::PostHandler::drop<data::Group>(args...);
        }
        else if (str_hash == hasher("group_student"))
        {
            res = post::PostHandler::drop<data::Group_student>(args...);
        }
        else if (str_hash == hasher("lesson"))
        {
            res = post::PostHandler::drop<data::Lesson>(args...);
        }
        else if (str_hash == hasher("journal_table"))
        {
            res = post::PostHandler::drop<data::Journal_table>(args...);
        }
        else if (str_hash == hasher("subject"))
        {
            res = post::PostHandler::drop<data::Subject>(args...);
        }
        else if (str_hash == hasher("mark"))
        {
            res = post::PostHandler::drop<data::Mark>(args...);
        }
        else if (str_hash == hasher("plan"))
        {
            res = post::PostHandler::drop<data::Plan>(args...);
        }
        else if (str_hash == hasher("theme"))
        {
            res = post::PostHandler::drop<data::Theme>(args...);
        }
        else if (str_hash == hasher("file"))
        {
            res = post::PostHandler::drop<data::File>(args...);
        }
        else if (str_hash == hasher("holiday"))
        {
            res = post::PostHandler::drop<data::Holiday>(args...);
        }
        else if (str_hash == hasher("problem"))
        {
            res = post::PostHandler::drop<data::Problem>(args...);
        }
        else if (str_hash == hasher("submission"))
        {
            res = post::PostHandler::drop<data::Submission>(args...);
        }
        else if (str_hash == hasher("user_upload"))
        {
            res = post::PostHandler::drop<data::User_upload>(args...);
        }
        else if (str_hash == hasher("plan_upload"))
        {
            res = post::PostHandler::drop<data::Plan_upload>(args...);
        }
        else if (str_hash == hasher("journal_upload"))
        {
            res = post::PostHandler::drop<data::Journal_upload>(args...);
        }
        else if (str_hash == hasher("journal_download"))
        {
            res = post::PostHandler::drop<data::Journal_download>(args...);
        }
        else if (str_hash == hasher("question"))
        {
            res = post::PostHandler::drop<data::Question>(args...);
        }
        else if (str_hash == hasher("question_type"))
        {
            res = post::PostHandler::drop<data::Question_type>(args...);
        }
        else if (str_hash == hasher("user_answer"))
        {
            res = post::PostHandler::drop<data::User_answer>(args...);
        }

        return res;
    }
};

} // namespace post
#endif // !POST_ROUTER
