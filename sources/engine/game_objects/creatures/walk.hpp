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
        float time;
    };

    Walk() = default;

    void setInfo(const std::vector<StopInfo>& stops_info);

    void walk(std::function<void(float, float)> setPosFunc,
              const glm::vec2& cur_pos);

private:
    std::vector<StopInfo> m_stops;
};
} // namespace kusengine

#endif // WALK_HPP
