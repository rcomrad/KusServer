#ifndef CROW_HELPER_HPP
#define CROW_HELPER_HPP

#include <string>

#include "crow.h"

namespace mult
{
class CrowHelper
{
public:
    static const std::string& getPart(const crow::multipart::message& aMsg,
                                      std::string aStr) noexcept;
};

}; // namespace mult

#endif // !CROW_HELPER_HPP
