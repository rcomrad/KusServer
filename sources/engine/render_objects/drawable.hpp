#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "render_object.hpp"

namespace kusengine
{

class Drawable
{
public:
    enum class ShapeType
    {
        RECTANGLE,
        CIRCLE,
        TRIANGLE,
        SPECIFIC
    };

    Drawable(ShapeType st);

    template <typename... Args>
    void create(Args&&... args);

    virtual ~Drawable() = default;

private:
    void createImpl(const MyVec2&, const MyVec2&); // RECTANGLE

    void createImpl(const MyVec2&, float radius, float freq); // CIRCLE

    void createImpl(const MyVec2&, const MyVec2&, const MyVec2&); // TRIANGLE

    ShapeType m_shape_type;

    std::unique_ptr<RenderObject> m_render_object;
};

template <typename... Args>
void
Drawable::create(Args&&... args)
{
    createImpl(std::forward<Args>(args)...);
}
}; // namespace kusengine

#endif // DRAWABLE_HPP
