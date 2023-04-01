#ifndef USER_HANDLER_HPP
#define USER_HANDLER_HPP

//--------------------------------------------------------------------------------

#include "database/connection_manager.hpp"
#include "database/data_request.hpp"

#include "get_handler.hpp"

//--------------------------------------------------------------------------------

namespace get
{
class UserHandler : public GetHandler
{
public:
    static crow::json::wvalue process(const std::vector<int>& aColumn,
                                      data::SmartConnection& aConnection) noexcept;

    static std::vector<std::string> mRoles;

private:
    static std::vector<std::string> getAllRoles() noexcept;
};
} // namespace get

//--------------------------------------------------------------------------------

#endif // !USER_HANDLER_HPP
