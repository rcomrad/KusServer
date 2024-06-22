#ifndef MULTITOOL_ROUTER_HPP
#define MULTITOOL_ROUTER_HPP

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "crow.h"
#include "multitool_handler.hpp"

namespace mult
{
class MultitoolRouter
{
public:
    static crow::response route(const crow::request& aReq);

private:
    struct Rote
    {
        decltype(&mult::MultiHandler::process) func;
        int roles;
    };

    static std::unordered_map<std::string, Rote> mMultitoolRouter;

    static std::unordered_map<std::string, Rote>
    generateMultitoolRouter() noexcept;
};

}; // namespace mult

#endif // !MULTITOOL_ROUTER_HPP
