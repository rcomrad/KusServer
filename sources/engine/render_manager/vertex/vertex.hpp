#ifndef VERTEX_HPP
#define VERTEX_HPP

namespace kusengine
{
namespace render
{
template <typename VertexAttributesT, typename VertexDescriptionT>
struct Vertex
{
public:
    using Description = VertexDescriptionT;
    using Attributes  = VertexAttributesT;

    Vertex(const Attributes& attributes) : m_attributes(attributes)
    {
    }

    const Attributes* const data() const
    {
        return &m_attributes;
    }

    static constexpr inline int countFloats()
    {
        return sizeof(Attributes) / sizeof(float);
    };

    Attributes m_attributes;
};

}; // namespace render
}; // namespace kusengine

#endif // VERTEX_HPP
