#include "walk.hpp"

namespace kusengine
{

void
Walk::setInfo(const std::vector<StopInfo>& stops_info)
{
    m_stops = stops_info;
}

void
Walk::walk(std::function<void(float, float)> setPosFunc,
           const glm::vec2& cur_pos)
{
    // setPosFunc()
}
}; // namespace kusengine
