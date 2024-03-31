#ifndef MULTITOOL_HANDLER_HPP
#define MULTITOOL_HANDLER_HPP

//--------------------------------------------------------------------------------

#include <set>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "database/connection_manager.hpp"
#include "database/raw_data.hpp"

#include "crow.h"

//--------------------------------------------------------------------------------

namespace mult
{

class MultiHandler
{
public:
    static std::string process(const crow::request& aReq) noexcept;
};

} // namespace mult

//--------------------------------------------------------------------------------

#endif // !MULTITOOL_HANDLER_HPP
