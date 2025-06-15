#ifndef WALK_HPP
#define WALK_HPP

#include <glm/vec2.hpp>

#include <functional>

namespace kusengine
{
class Walk
{
public:
    struct StopInfo
    {
        glm::vec2 position;
        float wait_time;
    };

    Walk();

    void setInfo(const std::vector<StopInfo>& stops_info);

    void walk(std::function<void(float, float)> setPosFunc,
              glm::vec2& cur_pos,
              float speed,
              float elapsed_time);

private:
    void takeStop();

    std::vector<StopInfo> m_stops;

    int cur_stop_index;

    float wait_time_left;
};
} // namespace kusengine

#endif // WALK_HPP
