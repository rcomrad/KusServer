#ifndef RESCHEDULE_HPP
#define RESCHEDULE_HPP

//--------------------------------------------------------------------------------

#include <crow.h>
#include <string>

//--------------------------------------------------------------------------------

namespace mult
{
class Reschedule
{
public:
    static std::string process(const crow::request& aReq) noexcept;

};
} // namespace mult

//--------------------------------------------------------------------------------

#endif // !RESCHEDULE_HPP
