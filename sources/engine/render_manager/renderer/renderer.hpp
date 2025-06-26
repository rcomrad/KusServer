#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>
#include <string_view>

// #include "engine/render_manager/renderer/render_way_type.hpp"

namespace kusengine
{
namespace render
{
template <typename DrawableSystemT>
class RenderInfo
{
public:
    using DrawableSystemType = DrawableSystemT;

    void setName(std::string_view name);

    std::string_view getName() const noexcept;

private:
    std::string m_name;
};
template <typename DrawableSystemT>
void
RenderInfo<DrawableSystemT>::setName(std::string_view name)
{
    m_name = name.data();
}

template <typename DrawableSystemT>
std::string_view
RenderInfo<DrawableSystemT>::getName() const noexcept
{
    return m_name;
}
}; // namespace render
}; // namespace kusengine

#endif // RENDERER_HPP
