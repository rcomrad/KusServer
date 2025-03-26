#ifndef MODEL_HPP
#define MODEL_HPP

#include "device.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include "helper_structs.hpp"
#include "texture_storage.hpp"

namespace kusengine
{

class Model
{
public:
    struct Vertex
    {
        glm::vec2 position;
        glm::vec2 uv;
        int texture_index;

        static std::vector<VkVertexInputBindingDescription>
        getBindingDescriptions();
        static std::vector<VkVertexInputAttributeDescription>
        getAttributeDescriptions();
    };

    Model(Device* device,
          const std::vector<Vertex>& vertices,
          const std::vector<uint16_t>& indeces);
    ~Model();

    Model(const Model&)            = delete;
    Model& operator=(const Model&) = delete;

    void bind(VkCommandBuffer command_buffer, VkPipelineLayout& pipelayout);
    void draw(VkCommandBuffer command_buffer);

    void move(float x, float y);

    void createIndexBuffer(const std::vector<uint16_t>& indeces);

    const VkDescriptorSetLayout* getSetLayoutsConstPtr();

private:
    void createVertexBuffer(const std::vector<Vertex>& vertices);
    void updateVertexBuffer();
    Device* m_device_ptr;

    std::vector<Vertex> m_vertices;
    Buffer m_vertex_buffer;
    ///
    std::vector<uint16_t> m_indices;
    Buffer m_index_buffer;
    ///
    void createDescriptorSetLayout(uint32_t textures_count);

    void createSampler();

    void createDescriptorSet();

    void createDescriptorPool();

    void updateDescriptorSet();

    TextureStorage m_texture_storage;

    uint32_t m_texture_count;

    VkSampler m_sampler;

    VkDescriptorSetLayout m_set_layout;

    VkDescriptorSet m_descriptor_set;

    VkDescriptorPool m_descriptor_pool;
};
}; // namespace kusengine

#endif // MODEL_HPP
