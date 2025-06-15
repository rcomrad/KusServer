#include "walk.hpp"

#include <glm/glm.hpp>

#include <iostream>
namespace kusengine
{

Walk::Walk() : cur_stop_index(0), wait_time_left(0)
{
}

void
Walk::setInfo(const std::vector<StopInfo>& stops_info)
{
    m_stops = stops_info;
}

void
Walk::takeStop()
{
    wait_time_left = m_stops[cur_stop_index].wait_time;
    cur_stop_index += 1;
    cur_stop_index %= m_stops.size();
}

void
Walk::walk(std::function<void(float, float)> setPosFunc,
           glm::vec2& cur_pos,
           float speed,
           float elapsed_time)
{
    wait_time_left -= elapsed_time;
    if (wait_time_left >= 0)
    {
        return;
    }
    else wait_time_left = 0;

    float distance = glm::distance(cur_pos, m_stops[cur_stop_index].position);

    float total_time = distance / speed;

    float t = elapsed_time / total_time;

    if (t >= 1)
    {
        // std::cout << cur_pos.x << " " << cur_pos.y << '\n';
        // std::cout << m_stops[cur_stop_index].position.x << " "
        //           << m_stops[cur_stop_index].position.y << '\n';
        // std::cout << "---------------\n";
        takeStop();
        return;
    }

    cur_pos = cur_pos + t * (m_stops[cur_stop_index].position - cur_pos);

    setPosFunc(cur_pos.x, cur_pos.y);
}
}; // namespace kusengine
