#include "request_map.hpp"

get::RequestMap&
get::RequestMap::getInstance() noexcept
{
    static RequestMap instance;
    return instance;
}
