#ifndef SCENE_HPP
#define SCENE_HPP

#include <glm/glm.hpp>

#include "engine/model/mesh/mesh_combiner.hpp"
#include "engine/model/model.hpp"
#include "engine/objects_data/dynamic_objects_data.hpp"
#include "engine/objects_data/uniform_buffer_object.hpp"
#include "engine/textures/texture_storage.hpp"

#include "camera.hpp"

namespace kusengine
{

class Scene
{
public:
    Scene() = default;

    void create(float width,
                float height,
                const TextureStorage& texture_storage_ptr);

    void render(const vk::CommandBuffer& command_buffer,
                const vk::PipelineLayout& pipelayout) const;

    // Shaders Data  //
    const UBO& ubo() const;

    const std::vector<DynamicObjectData>& dynamicObjectsData() const;

    // -------------- //

    const Camera2D& camera() const;

    void moveCamera(float x, float y, float z);

    void update(float time);

    //

    // void fillDescriptorSets(std::vector<vk::DescriptorSet>& d_sets) const;

    const vk::ClearValue& clearColor() const;

private:
    vk::ClearValue m_clear_value;
    // Textures

    const TextureStorage* m_texture_storage_ptr;

    // Models

    MeshCombiner m_mesh_combiner;

    // -----------  Models Data ----------- //

    std::vector<std::pair<Model, int>> m_models;
    std::vector<DynamicObjectData> m_dynamic_objects_data;

    // ----------- Moving Data ------------ //

    std::vector<std::array<float, 3>>
        circlec_moving_info; // angle, angle_speed, radius

    std::vector<std::array<float, 3>>
        circlec_color_info; // speed for x, y, and z

    // ------------------------------------- //

    UBO m_ubo;

    Camera2D m_camera;
};

}; // namespace kusengine

#endif // SCENE_HPP
