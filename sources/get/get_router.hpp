#ifndef GET_ROUTER_HPP
#define GET_ROUTER_HPP

#include "get_handler.hpp"

namespace get
{
class GetRouter
{
public:
    template <typename... Args>
    void getRouter(const data::TableInfoAray& request,
                   data::DBSettings& aDBS,
                   Args&&... args) noexcept
    {
        auto temp = request.popTableName();
        if (temp)
        {
            getRouter(request, aDBS, args..., );
        }
        else
        {
            get::GetHandler::process(request, aDBS, args...);
        }
    }

private:
};

} // namespace get
#endif // !GET_ROUTER
