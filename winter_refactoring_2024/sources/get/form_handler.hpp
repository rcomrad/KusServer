#ifndef GET_FORM_HANDLER_HPP
#define GET_FORM_HANDLER_HPP

//--------------------------------------------------------------------------------

#include "database/connection_manager.hpp"

#include "get_handler.hpp"

//--------------------------------------------------------------------------------

namespace get
{
class FormHandler : public GetHandler
{
public:
    static crow::json::wvalue process(
        const crow::request& aRequest,
        const std::unordered_set<int>& aColumn,
        data::SmartConnection& aConnection) noexcept;
};
} // namespace get

//--------------------------------------------------------------------------------

#endif // !GET_FORM_HANDLER_HPP
