#include "renderer.hpp"

namespace kusengine
{
namespace render
{
void
RenderInfo::setRenderWayType(RenderWayType rwt)
{
    m_render_way_type = rwt;
}

void
RenderInfo::setName(std::string_view name)
{
    m_name = name.data();
}

std::string_view
RenderInfo::getName() const noexcept
{
    return m_name;
}

RenderWayType
RenderInfo::getenderWayType() const noexcept
{
    return m_render_way_type;
}
}; // namespace render
}; // namespace kusengine
