#ifndef GET_QUESTION_HANDLER_HPP
#define GET_QUESTION_HANDLER_HPP

//--------------------------------------------------------------------------------

#include "database/connection_manager.hpp"
#include "database/data_request.hpp"

#include "get_handler.hpp"

//--------------------------------------------------------------------------------

namespace get
{
class QuestionHandler : public GetHandler
{
public:
    static crow::json::wvalue process(
        const std::vector<int>& aColumn,
        data::SmartConnection& aConnection) noexcept;
};
} // namespace get

//--------------------------------------------------------------------------------

#endif // !GET_QUESTION_HANDLER_HPP