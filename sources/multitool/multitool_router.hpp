#ifndef MULTITOOL_ROUTER_HPP
#define MULTITOOL_ROUTER_HPP

#include <unordered_map>

#include "crow.h"
#include "multitool_handler.hpp"

namespace mult
{
class MultitoolRouter
{
public:
    static std::string route(const crow::request& aReq);

private:
    static std::unordered_map<std::string,
                              decltype(&mult::MultiHandler::process)>
        mMultitoolRouter;
};

}; // namespace mult

#endif // !MULTITOOL_ROUTER_HPP
