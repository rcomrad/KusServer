#ifndef GET_USER_HANDLER_HPP
#define GET_USER_HANDLER_HPP

//--------------------------------------------------------------------------------

#include "database/connection_manager.hpp"

#include "get_handler.hpp"

//--------------------------------------------------------------------------------

namespace get
{
class UserHandler : public GetHandler
{
public:
    static crow::json::wvalue process(
        const crow::request& aRequest,
        const std::unordered_set<int>& aColumn,
        data::SmartConnection& aConnection) noexcept;
};
} // namespace get

//--------------------------------------------------------------------------------

#endif // !GET_USER_HANDLER_HPP
