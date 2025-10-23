#pragma once

#include "crow.h"

namespace server
{

class UserHandler
{
public:
    static crow::response autorisation(const crow::request& aReq) noexcept;

private:
};

} // namespace server

//--------------------------------------------------------------------------------
