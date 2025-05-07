#ifndef SCENE_HPP
#define SCENE_HPP

#include <glm/glm.hpp>

#include "engine/model/mesh/mesh_combiner.hpp"
#include "engine/model/model.hpp"
#include "engine/objects_data/dynamic_objects_data.hpp"
#include "engine/objects_data/uniform_buffer_object.hpp"

#include "camera.hpp"

namespace kusengine
{

class Scene
{
public:
    Scene() = default;

    void create(float width, float height);

    void draw(const vk::CommandBuffer& command_buffer) const;

    UBO ubo() const;

    const Camera2D& camera() const;

    Camera2D& camera();

    const DynamicObjectsData& dynamicObjectsData() const;

    void update(float time);

private:
    // Models

    MeshCombiner m_mesh_combiner;

    // -----------  Models Data ----------- //

    std::vector<std::pair<Model, int>> m_models;
    DynamicObjectsData m_dynamic_objects_data;

    // ----------- Moving Data ------------ //

    std::vector<std::array<float, 3>>
        circlec_moving_info; // angle, angle_speed, radius

    std::vector<std::array<float, 3>>
        circlec_color_info; // speed for x, y, and z

    // ------------------------------------- //

    // UBO m_ubo;

    Camera2D m_camera;
};

}; // namespace kusengine

#endif // SCENE_HPP
