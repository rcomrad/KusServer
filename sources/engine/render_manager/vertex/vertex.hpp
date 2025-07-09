#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vulkan/vulkan.hpp>

#include <vector>

namespace kusengine::render
{
struct Vertex
{
public:
    enum class Type
    {
        VERTEX_P2D_UV,
        VERTEX_P3D_UV
    };

    virtual ~Vertex();

    Vertex(Type vt, int count);

    int floatCount() const noexcept;

    void pushTo(std::vector<float>& arr);

    virtual vk::VertexInputBindingDescription getBindingDescription() const = 0;

    virtual std::vector<vk::VertexInputAttributeDescription>
    getAttributeDescriptions() const = 0;

protected:
    void setValue(float value, int index) noexcept;

private:
    std::vector<float> m_data;

    Type m_type;
};

}; // namespace kusengine::render

#endif // VERTEX_HPP
