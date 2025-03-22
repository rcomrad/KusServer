#ifndef MODEL_HPP
#define MODEL_HPP

#include "device.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace kusengine
{

class Model
{
public:
    struct Vertex
    {
        glm::vec2 position;
        glm::vec2 uv;

        static std::vector<VkVertexInputBindingDescription>
        getBindingDescriptions();
        static std::vector<VkVertexInputAttributeDescription>
        getAttributeDescriptions();
    };

    Model(Device* device, const std::vector<Vertex>& vertices);
    ~Model();

    Model(const Model&)            = delete;
    Model& operator=(const Model&) = delete;

    void bind(VkCommandBuffer command_buffer);
    void draw(VkCommandBuffer command_buffer);

    void move(float x, float y);

private:
    void createVertexBuffer(const std::vector<Vertex>& vertices);
    void updateVertexBuffer();

    std::vector<Vertex> m_vertices;

    Device* m_device_ptr;
    VkBuffer m_vertex_buffer;

    VkBuffer m_staging_buffer;

    VkDeviceMemory m_vertex_buffer_memory;
    uint32_t m_vertex_count;
};
}; // namespace kusengine

#endif // MODEL_HPP
