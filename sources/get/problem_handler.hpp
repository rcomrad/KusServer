#ifndef PROBLEM_HANDLER_HPP
#define PROBLEM_HANDLER_HPP

//--------------------------------------------------------------------------------

#include "database/connection_manager.hpp"

#include "get_handler.hpp"

//--------------------------------------------------------------------------------

namespace get
{
class ProblemHandler : public GetHandler
{
public:
    static crow::json::wvalue process(int aProblemID, int aUserID) noexcept;
};
} // namespace get

//--------------------------------------------------------------------------------

#endif // !PROBLEM_HANDLER_HPP
