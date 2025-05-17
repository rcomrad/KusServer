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
    static str::String process(const crow::request& aReq) noexcept;
};
} // namespace mult

//--------------------------------------------------------------------------------

#endif // !RESCHEDULE_HPP
