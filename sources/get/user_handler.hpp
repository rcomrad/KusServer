#ifndef USER_HANDLER_HPP
#define USER_HANDLER_HPP

//--------------------------------------------------------------------------------

#include "database/data_request.hpp"
#include "database/database_query.hpp"

#include "get_handler.hpp"

//--------------------------------------------------------------------------------

namespace get
{
class UserHandler : public GetHandler
{
public:
    static crow::json::wvalue process(const std::vector<int>& aColumn,
                                      data::DatabaseQuery& aDBQ) noexcept;

    static std::vector<std::string> mRoles;

private:
    static std::vector<std::string> getAllRoles() noexcept;
};
} // namespace get

//--------------------------------------------------------------------------------

#endif // !USER_HANDLER_HPP
