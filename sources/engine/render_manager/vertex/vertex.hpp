#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vulkan/vulkan.hpp>

#include <iostream>
#include <vector>

namespace kusengine::render
{
enum class VertexType
{
    VERTEX_P2D_UV,
    VERTEX_P3D_UV
};
template <typename Attribute_t>
struct Vertex
{
public:
    VertexType getType() const noexcept;

    virtual ~Vertex() = default;

    Vertex(VertexType vt);

    int byteSize() const noexcept;

    virtual void pushTo(std::vector<char>& arr) const;

    virtual void getDataFrom(const std::vector<char>& arr, size_t index);

    virtual vk::VertexInputBindingDescription getBindingDescription() const = 0;

    virtual std::vector<vk::VertexInputAttributeDescription>
    getAttributeDescriptions() const = 0;

protected:
    Attribute_t m_attributes;

private:
    VertexType m_type;
};

template <typename Attribute_t>
Vertex<Attribute_t>::Vertex(VertexType vt) : m_type(vt)
{
}

template <typename Attribute_t>
VertexType
Vertex<Attribute_t>::getType() const noexcept
{
    return m_type;
}

template <typename Attribute_t>
int
Vertex<Attribute_t>::byteSize() const noexcept
{
    return sizeof(m_attributes);
}

template <typename Attribute_t>
void
Vertex<Attribute_t>::pushTo(std::vector<char>& arr) const
{
    arr.resize(arr.size() + byteSize());

    void* beg = static_cast<void*>(&arr[arr.size() - byteSize()]);

    memcpy(beg, reinterpret_cast<const void*>(&m_attributes), byteSize());
}

template <typename Attribute_t>
void
Vertex<Attribute_t>::getDataFrom(const std::vector<char>& arr, size_t index)
{
    memcpy(static_cast<void*>(&m_attributes),
           static_cast<const void*>(arr.data() + index), byteSize());
}

}; // namespace kusengine::render

#endif // VERTEX_HPP
